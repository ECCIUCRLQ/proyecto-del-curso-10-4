#ifndef FILE_HPP
#define FILE_HPP

// file name length went from 31 to 22 (-1byte -4byte -4byte)
#define BLOCK_SIZE 512
#define FILE_NAME_LEN 22
#define POINTERS_SIZE 56

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Struct for storing a serialized File
 */
struct FileStruct {
  size_t fileBlock = 0;
  size_t parent = 0;
  size_t nextBlock = 0;
  size_t size = 0;
  size_t pointers[POINTERS_SIZE] = {0};
  int user = 0;
  int group = 0;
  char name[FILE_NAME_LEN] = {0};
  bool isDir = false;
  char permission = '\0';
};


/**
 * @brief Class that represents a File in a File System
 */
class File {
 protected:
  /**
   * @brief First block of the File
   */
  size_t block = 0;

  /**
   * @brief File/Folder Name
   */
  char name[FILE_NAME_LEN] = {0};

  /**
   * @brief Flag for diferentiating Directories from Files
   */
  bool _isDir = false;

  /**
  * @brief sort of Flag for user and group
  */
  int user = 0;
  int group = 0;

  /**
  * @brief stores permission of file
  */
  char permission;

  File* parent = nullptr;

 private:
  /**
   * @brief List of all the portions of the File.
   */
  std::pair<size_t, size_t> pors[POINTERS_SIZE];
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
  * @brief Constructor for File with permissions
  * @param fileName file name
  * @param int user
  * @param int group
  * @param char permission
  **/
  File(std::string fileName, int user, int group, char permission);
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
  virtual void serialize(FileStruct& fs);
  size_t getBlock();
  bool setBlock(size_t block);
  bool isDir();
  int getUser();
  int getGroup();
  char getPermission();
};


#endif
