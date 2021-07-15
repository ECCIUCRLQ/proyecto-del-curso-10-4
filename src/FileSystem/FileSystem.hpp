#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

// FILE SYSTEM
#include "Bitmap.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "HardDrive.hpp"

// UTILS
#include "Utils/Parser.hpp"

#include <cstddef>
#include <map>
#include <string>
#include <iostream>


#define BLOCK_SIZE 512

// 15 permissions to choose from
// last 4 bits represent permissions, i.e. 0100 >0001< only group can write = A
// 0100 >1001< group can read, user can write = F 
#define gWrite 'A'
#define gRead 'B'
#define gReadWrite 'C'
#define uWrite 'D'
#define uRead 'H'
#define uReadWrite 'L'
#define uWritegWrite 'E'
#define uReadgRead 'J'
#define ALLOW_ALL 'O'
#define uReadgWrite 'I'
#define uWritegRead 'F'
#define uReadgReadWrite 'K'
#define uReadWritegRead 'N'
#define uWritegReadWrite 'G' 
#define uReadWritegWrite 'M'

// use when calling verifypermission from a fileSystem function.
// use READ when opening, reading
// use WRITE when creating,deleting, writing
#define READ 'R'
#define WRITE 'W'


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
  bool createFile(std::string fileName, int user, int group, char permission);

  /**
   * @brief Read the content of a File
   * @param filepath Path of the File that is trying to be read
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return Array of chars containing the data. Nullptr on failure.
   */
  bool readFile(std::string filepath, char* dest, size_t len, int user, int group);

  /**
   * @brief Write some content into a File
   * @param filepath Path of the File that is trying to be written in
   * @param char* Array of chars to be stored
   * @param user User trying to access the File
   * @param group Group of the user trying to access the File
   * @return True on success, false on failure or access not granted
   */
  bool writeFile(std::string filepath, const char* data, size_t len, int user, int group);

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
  
  /**
   * @brief Open a File
   * @param filepath Path of the File that is trying to be opened
   * @param user User trying to open the File
   * @param group Group of the user trying to open the File
   * @return True on success, false on failure.
   */
  bool openFile(std::string filepath, int user, int group);
 
 
  /**
   * @brief Close  a File
   * @param filepath Path of the File that is trying to be closed
   * @param user User trying to close the File
   * @param group Group of the user trying to close the File
   * @return True on success, false on failure.
   */
  bool closeFile(std::string filepath, int user, int group);
 
   /**
   * @brief Check if a File is open
   * @param filepath Path of the File that is trying to be checked
   * @param user User trying to check if  the File open 
   * @param group Group of the user trying to check the File
   * @return True on success, false on failure.
   */
  bool isFileOpen(std::string filepath, int user, int group);

  size_t sizeOfFile(std::string filepath, int user, int group);
 

  /*
  * DIRECTORY MANAGEMENT METHODS
  */
 public:
  bool createDir(std::string dir, int user, int group, char permission);
  bool deleteDir(std::string dir, int user, int group);
  bool changeDir(std::string dir, int user, int group);
  char* dirList(std::string dir, int user, int group);

  /*
  * FILE SYSTEM UTILS
  */
 private:
  bool writeFile(size_t block, char* data, size_t len);
  bool writeBlock(size_t block, char* data, size_t len);
  std::string readBlocks(size_t block, size_t amount);
  File* search(std::vector<std::string>* splitPath, size_t pos, Directory* directory);
  char* getBlock(size_t pos);
  void serializeDirectory(Directory* dir);
  void serializeFile(File* file);
  bool verifyPermission(char permission, int user, int group,char accessPermission, int accessUser, int accessGroup);
  bool verifyUser(char permission, char accessPermission, bool verification);
  bool verifyGroup(char permission, char accessPermission, bool verification);
 public:
  File* search(const std::string& filepath);
  void serializeTree();
  void printBitmap() {
    this->spaceBitmap->print();
  };
  void printHD() {
    this->hardDrive->print();
  };
};


#endif
