#include "FileSystem.hpp"

#include <cstring>

FileSystem::FileSystem(const size_t& size, HardDrive* drive) : size(size),
  hardDrive(drive) {
  // Creates the Bitmap for free/used space in storage
  this->spaceBitmap = new Bitmap(this->size / BLOCK_SIZE);

  // Creates the root directory
  this->rootDirectory = new Directory("/");
  rootDirectory->setBlock(this->spaceBitmap->reserveFirstFreeBlock());
  this->serializeTree();

  // Always set the first block as used
  this->spaceBitmap->setBlockAs(0, BITMAP_USED_BLOCK);
}

FileSystem::~FileSystem() {
}

/*
 * FILE MANAGEMENT METHODS
*/

bool FileSystem::createFile(std::string fileName, int user, int group) {
  bool created = false;

  // TODO (any): Add a method to verify if path is relative or absolute
  std::string filePath = fileName;
  std::vector<std::string> splitPath = Parser::split(filePath, '/');

  File* found = this->search(filePath);
  if (found == nullptr) {
    // Verifies if the parent Directory exists
    std::string parentPath = Parser::parentDirectory(filePath, '/');
    Directory* parent;
    if (parentPath.length() == 0) {
      parent = rootDirectory;
    } else {
      parent = dynamic_cast<Directory*>(this->search(parentPath));
    }
    if (parent != nullptr) {
      // Creates a new File
      File* newFile = new File(fileName);

      // Adds the new File to the parent Directory
      parent->addFile(newFile);

      // The File was created
      created = true;

      // Reserves a block for the file, and sets it
      newFile->setBlock(this->spaceBitmap->reserveFirstFreeBlock());

      // Re serialize the FS
      this->serializeTree();
    }
  }

  return created;
}

bool FileSystem::writeFile(std::string filepath, const char* data, size_t len, int user, int group) {
  bool ret = false;

  // Search for the File
  File* file = this->search(filepath);
  if (file != nullptr) {
    // Opens the File
    if (this->openFile(filepath, user, group)) {
      // Calculates the amount of blocks needed for the file
      size_t blocksNeeded = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

      // Reserves blocks for the data
      auto portions = this->spaceBitmap->reserveBlocks(blocksNeeded);

      // TODO(any): file size must increase

      // Divides the data in chunks for each portion
      size_t pos = 0;
      for (auto p : portions) {
        file->addPortion(p.first, p.second);

        size_t chunkSize = (p.second - p.first + 1) * BLOCK_SIZE;

        if (pos + chunkSize > len) {
          chunkSize = len % chunkSize;
        }

        char* chunk = new char[chunkSize + 1];
        chunk[chunkSize] = 0;
        std::memcpy(chunk, &data[pos], chunkSize);

        this->writeFile(p.first, chunk, chunkSize);

        delete[] chunk;
        pos += chunkSize;
      }

      // Serializes the tree
      this->serializeTree();
    }
  }

  return ret;
}

bool FileSystem::writeFile(size_t block, char* data, size_t len) {
  bool ret = false;

  if (len > 0) {
    // Calculates how many blocks are needed to store data
    size_t amountOfBlocks = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;
    size_t count = 0;

    // Writes the first n-1 full blocks
    for (size_t i = 0; i < amountOfBlocks; ++i) {
      char chunk[BLOCK_SIZE];
      size_t chunkSize = 0;
      // If still not the last chunk or exact last chunk
      if (count < amountOfBlocks - 1) {
        chunkSize = BLOCK_SIZE;
      } else {
        // If last chunk is not exact
        chunkSize = len - (count * BLOCK_SIZE);
      }

      // Writes the chunk
      std::memcpy(chunk, &data[count * BLOCK_SIZE], chunkSize);
      this->writeBlock(block + count, chunk, chunkSize);
      ++count;
    }

    ret = true;
  }
  
  return ret;
}

bool FileSystem::writeBlock(size_t block, char* data, size_t len) {
  bool ret = false;

  if (block < this->spaceBitmap->getAmountOfBlocks()) {
    // Calculates the pos of the block
    size_t pos = block * BLOCK_SIZE;

    // Gets the first byte for the block
    char* storage = this->hardDrive->getPos(pos);

    // Write len bytes on storage
    for (size_t i = 0; i < len; ++i) {
      storage[i] = data[i];
    }

    ret = true;
  }

  return ret;
}

File* FileSystem::search(const std::string& filePath) {
  File* ret = nullptr;

  // Split the filePath
  std::vector<std::string> splitPath = Parser::split(filePath, '/');

  ret = this->search(&splitPath, 0, rootDirectory);

  return ret;
}

File* FileSystem::search(std::vector<std::string>* splitPath, size_t pos, Directory* directory) {
  File* ret = nullptr;

  // Stop condition
  if (pos == splitPath->size() - 1) {
    ret = directory->search(splitPath->at(pos));
  } else {
    // Continues searching
    File* nextFile = directory->search(splitPath->at(pos));
    Directory* nextDir = dynamic_cast<Directory*>(nextFile);
    if (nextDir != nullptr) {
      ret = search(splitPath, pos + 1, nextDir);
    }
  }

  return ret;
}

bool FileSystem::deleteFile(const std::string& filePath, int user, int group) {
  bool ret = false;
  File* file = this->search(filePath);

  if (file != nullptr) {
    // Get the parent of the File/Directory
    File* parentFile = file->getParent();
    Directory* parent = dynamic_cast<Directory*>(parentFile);

    // Delete the File from the parent
    if (parent != nullptr) {
      parent->deleteFile(file);
    }

    // Get all the portions of the File
    auto portions = file->getAllPortions();

    // Set all the blocks of the portions to Free
    for (auto portion : portions) {
      for (size_t i = portion.first; i <= portion.second; ++i) {
        this->spaceBitmap->setBlockAs(i, BITMAP_FREE_BLOCK);
      }
    }
    
    // Delete the File
    delete file;
  }

  return ret;
}


bool FileSystem::openFile(std::string filepath, int user, int group){
	bool open = false;
  File* file = this->search(filepath);

	if(file != nullptr){
		file->open();
		open = true;
	}
	
	return open;
}

bool FileSystem::closeFile(std::string filepath, int user, int group){
	bool closed = false;
  File* file = this->search(filepath);

	if(file != nullptr){
		file->close();
		closed = true;
	}
	
	return closed;
}

bool FileSystem::isFileOpen(std::string filepath, int user, int group){
	bool fileOpen = false;
	if(search(filepath) != nullptr){
		fileOpen = search(filepath)->isOpen();
	}
	return fileOpen;
}

void FileSystem::serializeTree() {
  this->serializeDirectory(this->rootDirectory);
}

void FileSystem::serializeDirectory(Directory* dir) {
  // Serialize the current Dir
  this->serializeFile(dir);

  auto f = dir->list();

  // Serialize the subfiles
  for (auto file : dir->list()) {
    if (file != nullptr) {
      if (file->isDir()) {
        Directory* nextDir = dynamic_cast<Directory*>(file);
        serializeDirectory(nextDir);
      } else {
        this->serializeFile(file);
      }
    }
  }
}

void FileSystem::serializeFile(File* file) {
  // Get the block for the File
  size_t blockForFile = file->getBlock();
  if (blockForFile > 0) {
    // Sets the file block to blockForFile
    file->setBlock(blockForFile);

    // Gets the serialized data for the block
    FileStruct data;
    if (file->isDir()) {
      Directory* dir = dynamic_cast<Directory*>(file);
      dir->serialize(data);
    } else {
      file->serialize(data);
    }

    // Writes the File to disk
    char* byte = this->hardDrive->getPos(blockForFile * BLOCK_SIZE);
    std::memcpy(byte, &data, sizeof(data));
  }
}
