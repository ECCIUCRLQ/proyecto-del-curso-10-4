// Copyright 2021 Equipo Tronaditas

#include "Bitmap.hpp"

Bitmap::Bitmap(size_t size) : amountOfBlocks(size) {
  // Amount of bytes for the block array
  size_t bytes = size / 8 + (size % 8 != 0);

  // Reserves 'bytes' bytes for the array
  this->blocks.resize(bytes);

  // Sets the first block as used
  this->setBlockAs(0, BITMAP_USED_BLOCK);
}

Bitmap::~Bitmap() {
}

bool Bitmap::blockIsFree(size_t block) {
  bool ret = false;

  // Check if block is valid
  if (block < this->amountOfBlocks) {
    // Gets the byte for the block. Block divided by 8 (byte size).
    size_t byte = block / 8;

    // Bit of the block inside its byte
    unsigned int bit = block % 8;

    ret = this->blockIsFree(byte, bit);
  }

  return ret;
}

bool Bitmap::blockIsFree(size_t bytePos, unsigned int bit) {
  bool ret = false;

  // Validates the bit
  if (bit < 8) {
    // Gets the byte from the array
    unsigned char byte = this->blocks[bytePos];

    // Checks if the requested bit is 0 or 1
    ret = (byte & (1 << bit)) == 0;
  }

  return ret;
}

bool Bitmap::setBlockAs(size_t block, bool status) {
  bool ret = false;

  // Validates the block position. Also checks if the value will be changed
  if (block < this->amountOfBlocks && status == this->blockIsFree(block)) {
    // Gets the byte for the block. Block divided by 8 (byte size).
    char byte = this->blocks[block / 8];

    // Number of bit to toggle
    unsigned int bit = block % 8;

    // Mask for bit operation
    unsigned char mask = 1UL << bit;

    // Toggles the requested bit. Logical XOR 
    unsigned char newByte = byte ^ mask;

    // Updates the byte in the blocks vector
    this->blocks[block / 8] = newByte;

    ret = true;
  }

  return ret;
}

size_t Bitmap::firstFreeBlock() {
  size_t ret = 0;

  for (size_t i = 0; i < this->blocks.size(); ++i) {
    // If not all the blocks in the byte are used
    if (this->blocks[i] < 255) {
      // Position of the First block in the byte
      size_t firstBlockOfByte = i * 8;

      // Checks which bit in the byte is the first free one
      for (size_t j = firstBlockOfByte; j < firstBlockOfByte + 8 && ret == 0; ++j) {
        if (this->blockIsFree(j)) {
          ret = j;
        }
      }
    }
  }
  
  return ret;
}

std::vector<std::pair<size_t, size_t>> Bitmap::reserveBlocks(size_t amountOfBlocks) {
  std::vector<std::pair<size_t, size_t>> ret;

  size_t reserved = 1;
  bool noSpace = false;

  while (reserved < amountOfBlocks && !noSpace) {
    size_t first = this->firstFreeBlock();
    if (first != 0) {
      size_t second = first;

      // Gets a contiguous portion of blocks
      while (this->blockIsFree(second + 1) && reserved < amountOfBlocks) {
        ++second;
        ++reserved;
      }

      // Sets the blocks as used
      for (size_t i = first; i <= second; ++i) {
        this->setBlockAs(i, BITMAP_USED_BLOCK);
      }
      
      ret.push_back(std::make_pair(first, second));
    } else {
      noSpace = true;
    }
  }

  return ret;
}

size_t Bitmap::getAmountOfBlocks() {
  return this->amountOfBlocks;
}
