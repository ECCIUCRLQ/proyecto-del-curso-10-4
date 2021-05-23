#ifndef FILE_HPP
#define FILE_HPP

#define BLOCK_SIZE 512
#define FILE_NAME_LEN 40

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Class that represents a File in a File System
 */
class File {
 protected:
  /**
   * @brief Flag for diferentiating Directories from Files
   */
  bool isDir = false;
  
  /**
   * @brief File/Folder Name
   */
  char name[FILE_NAME_LEN] = {0};

  File* parent = nullptr;

 private:
  /**
   * @brief List of all the portions of the File.
   */
  // [10, 12]
  // [14, 14]
  std::vector<std::pair<size_t, size_t>> portions;

  /**
   * @brief Flag for indicating if a file is open
   */
  bool _isOpen = false;

  /**
   * @brief Contador de bytes
   */
  size_t size = 0;

  File* nextBlock = nullptr;

 public:
  File() = delete;

  /**
   * @brief Constructor for a File
   * @param fileName name of the File
   */
  explicit File(std::string fileName);

  /**
   * @brief Constructor for a File
   * @param fileName name of the File
   * @param block TODO
   */
  File(std::string fileName, size_t block);

  /**
   * @brief Destructor for a File
   */
  virtual ~File();

 public:
  /**
   * @brief Returns the size of the File in bytes
   * @return the size of the File in bytes
   */
  size_t getSize();

  /**
   * @brief Get function for the name of the File
   * @return A string with the name of the File
   */
  std::string getName();

  //
  void open();
  void close();
  bool isOpen();
  void addPortion(size_t block1,size_t block2);
  File* getParent();
  std::vector<std::pair<size_t, size_t>> getAllPortions();
};


#endif
