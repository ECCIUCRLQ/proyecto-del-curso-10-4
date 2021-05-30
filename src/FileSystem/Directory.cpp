#include "Directory.hpp"

#include <cstring>
#include <iostream>

Directory::Directory(std::string dirName) : File(dirName) {
  this->_isDir = true;
}

Directory::~Directory() {
  delete this->nextBlock;
}

File* Directory::search(const std::string& fileName) {
  File* ret = nullptr;

  // Verifies if this block of the Directory contains the File
  for (size_t i = 0; !ret && i < containedFilesCounter; ++i) {
    std::string containedFile = Parser::addUntilNull(this->containedFiles[i]->getName());
    if (containedFile.compare(fileName) == 0) {
      ret = this->containedFiles[i];
    }
  }

  // If the Directory continues in another block and the File hasn't been found
  // continues the search in the next block
  if (!ret && this->nextBlock != nullptr) {
    ret = this->nextBlock->search(fileName);
  }
  
  return ret;
}

bool Directory::addFile(File* file) {
  bool ret = true;

  if (containedFilesCounter < (BLOCK_SIZE - FILE_NAME_LEN - 8) / 8) {
    this->containedFiles[containedFilesCounter] = file;
    ++containedFilesCounter;
  } else {
    if (nextBlock != nullptr) {
      nextBlock->addFile(file);
    } else {
      Directory* newBlock = new Directory(std::string(this->name, FILE_NAME_LEN));
      this->nextBlock = newBlock;
      nextBlock->addFile(file);
    }
  }

  return ret;
}

bool Directory::deleteFile(File* file) {
  bool ret = false;

  // Tries to delete the File in this Block
  for (size_t i = 0; i < this->containedFilesCounter && !ret; ++i) {
    if (this->containedFiles[i] == file) {
      this->containedFiles[i] = nullptr;
      ret = true;
    }
  }

  // If the File in the next Block
  if (!ret && this->nextBlock != nullptr) {
    ret = nextBlock->deleteFile(file);
  }

  return ret;
}

std::vector<File*> Directory::list() {
  std::vector<File*> ret;

  for (size_t i = 0; i < POINTERS_SIZE; ++i) {
    ret.push_back(this->containedFiles[i]);
  }

  return ret;
}

void Directory::serialize(FileStruct& fs) {
  // Copy the name
  std::memcpy(fs.name, this->name, FILE_NAME_LEN);

  // Copy the amount of contained Files
  fs.size = this->containedFilesCounter;

  // This is a dir
  fs.isDir = true;

  // Copy parent
  if (this->parent != nullptr) {
    fs.parent = this->parent->getBlock();
  }

  // Copy next block
  if (this->nextBlock != nullptr) {
    fs.nextBlock = this->nextBlock->getBlock();
  }

  // Copy the portions
  for (size_t i = 0; i < this->containedFilesCounter; ++i) {
    fs.pointers[i] = this->containedFiles[i]->getBlock();
  }
}
