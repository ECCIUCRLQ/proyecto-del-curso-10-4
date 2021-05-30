#include "HardDrive.hpp"

#include <iostream>

HardDrive::HardDrive(const size_t& size) : size(size) {
  this->data.resize(this->size);
  for (size_t i = 0; i < this->size; ++i) {
    this->data[i] = 0;
  }
}

HardDrive::~HardDrive() {
}

size_t HardDrive::getSize() {
  return this->size;
}

char* HardDrive::getPos(const size_t& pos) {
  char* ret = nullptr;

  // Verifies if the position is valid
  if (pos < this->data.size()) {
    ret = &this->data.data()[pos];
  }

  return ret;
}

void HardDrive::print() {
  size_t lineSize = 512;
  size_t count = 0;
  for (size_t i = 0; i < this->size; i += lineSize) {
    std::cout << "Block " << count << std::endl;
    for (size_t j = 0; j < lineSize; ++j) {
      size_t pos = i + j;
      if (pos < this->size) {
        if (this->data[pos] > 32) {
          std::cout << this->data[pos];
        } else {
          std::cout << (int)this->data[pos];
        }
      }
    }
    ++count;
    std::cout << std::endl;
  }
  
}