#include "FileSystem.hpp"

#include <cstring>
#include <bitset>
#include <iostream>

FileSystem::FileSystem(const size_t& size, HardDrive* drive) : hardDrive(drive),
size(size) {
  // Creates the Bitmap for free/used space in storage
  this->spaceBitmap = new Bitmap(this->size / BLOCK_SIZE);

  // Creates the root directory
  this->rootDirectory = new Directory("/");
  rootDirectory->setBlock(this->spaceBitmap->reserveFirstFreeBlock());
  this->serializeTree();

  // Always set the first block as use
  this->spaceBitmap->setBlockAs(0, BITMAP_USED_BLOCK);
}

FileSystem::~FileSystem() {
}

/*
 * FILE MANAGEMENT METHODS
*/

bool FileSystem::createFile(std::string fileName, int user, int group, char permission) {
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
      if (true/*this->verifyPermission(parent->getPermission(), parent->getUser(), parent->getGroup(),WRITE, user, group)*/){
 	  // Creates a new File with user, group, permission
      File* newFile = new File(fileName, user, group, permission);


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
  }

  return created;
}

bool FileSystem::readFile(std::string filepath, char* dest, size_t len, int user, int group) {
  bool ret = false;

  // Search for the file
  File* file = this->search(filepath);
  Directory* directory = dynamic_cast<Directory*>(file);

  // Read only if file is no Dir
  if (directory == nullptr) {
    // Permisions to open file is same as read
    if (this->openFile(filepath, user, group)) {
      // Blocks to read
      auto portions = file->getAllPortions();
      size_t bytesRead = 0;

      for (auto p : portions) {
        size_t amountOfBlocks = p.second - p.first + 1;
        size_t portionBytes = amountOfBlocks * BLOCK_SIZE;
        bytesRead += portionBytes;

        // Read the data of the portion
        std::string portionData = this->readBlocks(p.first, amountOfBlocks);

        // Add all read bytes to ret
        if (bytesRead <= file->getSize()) {
          portionData.copy(dest, portionData.length());
        } else {
          // Add just the remaining bytes to the string
          size_t remainingBytes = bytesRead - (bytesRead - file->getSize());
          portionData.copy(dest, remainingBytes);
        }

        ret = true;
      }
    }
  }

  return ret;
}

std::string FileSystem::readBlocks(size_t block, size_t amount) {
  std::string ret;

  // If block is valid
  if (block > 0) {
    char* hdData = this->hardDrive->getPos(block * BLOCK_SIZE);
    ret.assign(hdData, amount * BLOCK_SIZE);
  }

  return ret;
}

bool FileSystem::writeFile(std::string filepath, const char* data, size_t len, int user, int group) {
  bool ret = false;

  // Search for the File
  File* file = this->search(filepath);
  if (file != nullptr) {
    // Opens the File
    if (this->openFile(filepath, user, group)) {
      if (verifyPermission(file->getPermission(), file->getUser(), file->getGroup(), WRITE, user, group)) {
        // Calculates the amount of blocks needed for the file
        size_t blocksNeeded = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

        // Reserves blocks for the data
        auto portions = this->spaceBitmap->reserveBlocks(blocksNeeded);

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

        // Increase file size
        file->increaseSize(len);

        // Serializes the tree
        this->serializeTree();

        ret = true;
      } else {
        std::cout << "Error 3" << std::endl;
      }
    } else {
      std::cout << "Error 2" << std::endl;
    }
  } else {
    std::cout << "Error 1" << std::endl;
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
      //verify if you can delete the file (can write)
      if (verifyPermission(file->getPermission(), file->getUser(), file->getGroup(), WRITE, user, group)) {
        parent->deleteFile(file);
      }
      
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

// agregar verificar permiso para leer
bool FileSystem::openFile(std::string filepath, int user, int group){
	bool open = false;
  File* file = this->search(filepath);
  
  if(file != nullptr){
  	if (this->verifyPermission(file->getPermission(), file->getUser(), file->getGroup(),READ,user,group)) {
  		file->open();
  		open = true;
  	}

   // return open;

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

size_t FileSystem::sizeOfFile(std::string filepath, int user, int group) {
  size_t ret = 0;
  File* file = this->search(filepath);
  Directory* directory = dynamic_cast<Directory*>(file);

  // If it is not a directory
  if (directory == nullptr) {
    // Verify permisions?
    ret = file->getSize();
  }

  return ret;
}

//METODO TEMPORAL
/**
* @brief verifies file permissions
* @param char permission file permission
* @param int fileUser file user
* @param int fileGroup file group
* @param char accessPermission permission to test for
* @param int accessUser user trying to access file function
* @param int accessGroup group trying to access file function
*/
bool FileSystem::verifyPermission(char permission, int fileUser, int fileGroup,
  char accessPermission, int accessUser, int accessGroup) {
  bool good2Go = false;
  // TODO change verifications to bit operations
  // TODO move permission check for group and file to different functions  (modularizar)
  //by group, check all relating to groups
  // if permission allows all, good to go
  if (fileGroup == accessGroup) {
    good2Go =this->verifyGroup(permission, accessPermission, good2Go);
  }
  //by user
  if (fileUser == accessUser) {
    good2Go = this->verifyUser(permission, accessPermission, good2Go);
  }
  // verify for following:
  // case: FILE
  // create/write
  // leer (read)



  return good2Go;
}
bool FileSystem::verifyGroup(char permission, char accessPermission, bool verification) {
  std::bitset<8> bits(permission);
  bool good2Go = verification;
  // if it allows all as a group
  if (permission == ALLOW_ALL ) {
    good2Go = true;
  }
  // Checks if you can read as a group
  if (accessPermission == READ) {
    if (bits[1] == 1) {
      good2Go = true;
    }
  // Checks if you can write as a group
  } else if (accessPermission == WRITE) {
    if (bits[0] == 1) {
      good2Go = true;
    }
  }
  return good2Go;
}

bool FileSystem::verifyUser(char permission, char accessPermission, bool verification) {
  std::bitset<8> bits(permission);
  bool good2Go = verification;
  // if it allows all as a user
  if (permission == ALLOW_ALL ) {
    good2Go = true;
  }
  // Checks if you can read as a user
  if (accessPermission == READ) {
    if (bits[3] == 1) {
      good2Go = true;
    }
  // Checks if you can write as a user
  } else if (accessPermission == WRITE) {
    if (bits[2] == 1) {
      good2Go = true;
    }
  }

  return good2Go;
}
