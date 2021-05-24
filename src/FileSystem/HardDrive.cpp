#include "HardDrive.hpp"

#include <iostream>

HardDrive::HardDrive(const size_t& size) : size(size) {
  this->data.resize(this->size);
  for (size_t i = 0; i < this->size; ++i) {
    this->data[i] = '0';
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
  for (size_t i = 0; i < this->size; i += 100) {
    for (size_t j = 0; j < 100; ++j) {
      size_t pos = i + j;
      if (pos < this->size) {
        std::cout << this->data[pos];
      }
    }
    std::cout << std::endl;
  }
  
}