#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#define BLOCK_SIZE 512

#include <cstddef>
#include <map>
#include <string>

#include "Bitmap.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "HardDrive.hpp"

#include "Utils/Parser.hpp"

/**
 * @brief File System that allows reading from and writing on a Hard Drive.
 */
class FileSystem {
 protected:
  /**
   * @brief Hard Drive in which the File System is stored
   */
  HardDrive* hardDrive;

  /**
   * @brief Size of the File System in bytes
   */
  size_t size;

  /**
   * @brief Bitmap of used and free space
   */
  Bitmap* spaceBitmap;

  /**
   * @brief Active directory in the File System
   */
  Directory* currentDirectory = nullptr;

  /**
   * @brief Active Directory in the File System represented as a string
   */
  std::string currentDirectoryS = "";

  /**
   * @brief Root directory of the File System
   */
  Directory* rootDirectory = nullptr;

 public:
  /**
   * @brief Constructor for a File System
   * @param size Size of the File System in bytes
   */
  FileSystem(const size_t& size, HardDrive* drive);

  /**
   * @brief Destructor for a File System
   */
  ~FileSystem();


  /*
  * FILE MANAGEMENT METHODS
  */
 public:
  /**
   * @brief Create a File in the File System
   * @param fileName Name for the File
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return True on success, false if the File could not be created
   */
  bool createFile(std::string fileName, int user, int group);

  /**
   * @brief Read the content of a File
   * @param filepath Path of the File that is trying to be read
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return Array of chars containing the data. Nullptr on failure.
   */
  unsigned char* readFile(std::string filepath, int user, int group);

  /**
   * @brief Write some content into a File
   * @param filepath Path of the File that is trying to be written in
   * @param char* Array of chars to be stored
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return True on success, false on failure or access not granted
   */
  bool writeFile(std::string filepath, char* data, int user, int group);

  /**
   * @brief Append some data to a File
   * @param filepath Path of the File that is trying to be written in
   * @param char* Array of chars to be appended
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return True on success, false on failure or access not granted
   */
  bool appendFile(std::string filepath, char* data, int user, int group);

  /**
   * @brief Delete a File
   * @param filepath Path of the File that is trying to be deleted
   * @param user User trying to delete the File
   * @param group Group of the user trying to delete the File
   * @return True on success, false on failure.
   */
  bool deleteFile(const std::string& filepath, int user, int group);
  
  
  bool openFile(std::string filepath, int user, int group);
  /**
   * @brief Close a File
   * @param filepath Path of the File that is trying to be closed
   * @param user User trying to close the File
   * @param group Group of the user trying to close the File
   * @return True on success, false on failure.
   */

  /*
  * DIRECTORY MANAGEMENT METHODS
  */
 public:
  bool createDir(std::string dir, int user, int group);
  bool deleteDir(std::string dir, int user, int group);
  bool changeDir(std::string dir, int user, int group);
  char* dirList(std::string dir, int user, int group);

  /*
  * FILE SYSTEM UTILS
  */
 private:
  File* search(std::vector<std::string>* splitPath, size_t pos, Directory* directory);
 public:
  File* search(const std::string& filepath);
  char* getBlock(size_t pos);
};


#endif
