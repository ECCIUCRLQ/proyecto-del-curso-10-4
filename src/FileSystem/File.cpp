#include <cstring>

#include <iostream>

#include "File.hpp"

File::File(std::string fileName) {
  std::strncpy(this->name, fileName.c_str(), FILE_NAME_LEN - 1);
  this->name[FILE_NAME_LEN - 1] = 0;
}

File::File(std::string fileName, size_t block) {
  std::strncpy(this->name, fileName.c_str(), FILE_NAME_LEN);
  this->addPortion(block, block);
}

File::~File() {
}

std::string File::getName() {
  return std::string(this->name, FILE_NAME_LEN);
}

void File::open() {
	this->_isOpen = true;
}

void File::close() {
	this->_isOpen = false;
}

bool File::isOpen() {
	return this->_isOpen;
}

void File::addPortion(size_t block1, size_t block2) {
	auto pair = std::make_pair(block1, block2);
  portions.push_back(pair);
}

File* File::getParent() {
  return this->parent;
}

std::vector<std::pair<size_t, size_t>> File::getAllPortions() {
  std::vector<std::pair<size_t, size_t>> ret;
  
  // Add the current Block 
  ret.insert(ret.end(), this->portions.begin(), this->portions.end());

  // Add the next block if it exists
  if (this->nextBlock != nullptr) {
    std::vector<std::pair<size_t, size_t>> nextPortions = nextBlock->getAllPortions();
    ret.insert(ret.end(), nextPortions.begin(), nextPortions.end());
  }

  return ret;
}

void File::serialize(FileStruct& fs) {
  // Copy the name
  std::memcpy(fs.name, this->name, FILE_NAME_LEN);

  // Copy the size of the file
  fs.size = this->size;

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
  size_t pos = 0;
  for (auto p : this->portions) {
    fs.pointers[pos] = p.first;
    fs.pointers[pos + 1] = p.second;
    pos += 2;
  }
}

size_t File::getBlock() {
  return this->block;
}

bool File::setBlock(size_t block) {
  bool ret = false;

  if (block > 0) {
    this->block = block;
    ret = true;
  }
  
  return ret;
}

bool File::isDir() {
  return this->_isDir;
}