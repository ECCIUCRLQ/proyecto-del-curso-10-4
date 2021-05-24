// Copyright 2021 Equipo Tronaditas

#ifndef BITMAP_HPP
#define BITMAP_HPP

#define BITMAP_FREE_BLOCK 0
#define BITMAP_USED_BLOCK 1

#include <cstddef>
#include <vector>

class Bitmap {
 private:
  size_t amountOfBlocks = 0;
  /**
   * @brief Array of blocks of a File System.
   * @details Each bit of the array represents one block. 0 means it's free, 1 otherwise.
   */
  std::vector<char> blocks;

 public:
  /**
   * @brief Default constructor deleted
   */
  Bitmap() = delete;

  /**
   * @brief Constructor for a bitmap with 'size' amount of blocks
   * @param size Amount of blocks in the bitmap
   */
  explicit Bitmap(size_t size);

  /**
   * @brief Default destructor for a Bitmap
   */
  ~Bitmap();

 public:
  /**
   * @brief Returns the value of amountOfBlocks
   * @return The value of amountOfBlocks
   */
  size_t getAmountOfBlocks();

 private:
  /**
   * @brief Verifies if a block is free or not
   * @param bytePos position of the byte in which the block is stored
   * @param bit number of bit in the byte that represents the block
   * @return True if the bit is free, false otherwise
   */
  bool blockIsFree(size_t bytePos, unsigned int bit);

 public:
  /**
   * @brief Verifies if a block is free or not
   * @param block Position of the block to be checked
   * @return True if the block is free, false otherwise
   */
  bool blockIsFree(size_t block);

  /**
   * @brief Finds the first free block in the File System
   * @return Position of the first free block in the File System
   */
  size_t firstFreeBlock();

  /**
   * @brief Changes the state of a block to used or free
   * @param block Position of the block to change
   * @param status The status for the block. BITMAP_FREE_BLOCK or BITMAP_USED_BLOCK
   * @return True on success, false otherwise
   */
  bool setBlockAs(size_t block, bool status);

  /**
   * @brief Reserves an amount of blocks.
   * @details Tries to reserve the max amount of contiguous blocks
   * @param amountOfBlocks amount of blocks to reserve
   * @return a vector containing the contigous portions of blocks reserved
   */
  std::vector<std::pair<size_t, size_t>> reserveBlocks(size_t amountOfBlocks);
};


#endif
