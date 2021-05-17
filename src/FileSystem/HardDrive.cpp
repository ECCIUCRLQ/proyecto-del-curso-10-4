#include "HardDrive.hpp"

HardDrive::HardDrive(const size_t& size) : size(size) {
}

HardDrive::~HardDrive() {
}

size_t HardDrive::getSize() {
  return this->size;
}

unsigned char* HardDrive::getPos(const size_t& pos) {
  unsigned char* ret = nullptr;

  // Verifies if the position is valid
  if (pos < this->data.size()) {
    ret = &this->data.data()[pos];
  }

  return ret;
}
