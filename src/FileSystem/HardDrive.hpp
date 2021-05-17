#ifndef HARD_DRIVE_HPP
#define HARD_DRIVE_HPP

#include <cstddef>
#include <vector>

/**
 * @brief Simulates a hard drive for storing data.
 */
class HardDrive {
 protected:
  /**
   * @brief Size of the Hard Drive in bytes
   */
  size_t size;

  /**
   * @brief Stores all the data in the Hard Drive
   */
  std::vector<unsigned char> data;

 public:
  /**
   * @brief Constructs a Hard Drive of a defined size
   * @param size Size (in bytes) of the Hard Drive.
   */
  explicit HardDrive(const size_t& size);

  /**
   * @brief Destructor for HardDrive
   */
  ~HardDrive();

 public:
  /**
   * @brief Returns the size of the Hard Drive in bytes
   * @return the size of the Hard Drive in bytes
   */
  size_t getSize();

  /**
   * @brief Returns a pointer to the requested position of the Hard Drive.
   * @param pos Requested position of the Hard Drive
   * @return A pointer to the requested position. Nullptr if the position cannot be accessed
   */
  unsigned char* getPos(const size_t& pos);
};


#endif
