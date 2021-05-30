#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <cstddef>
#include <vector>

#include "File.hpp"
#include "Utils/Parser.hpp"

class Directory : public File {
 protected:
  /**
   * @brief List of files and directories contained in the directory
   */
  File* containedFiles[POINTERS_SIZE];

  /**
   * @brief Counter for the Files contained in containedFiles
   */
  size_t containedFilesCounter = 0;

  /**
   * @brief Pointer to the next block of the Directory
   */
  Directory* nextBlock = nullptr;

 public:
  Directory() = delete;

  /**
   * @brief DefaultConstructor for a Directory
   * @param dirName name of the Directory
   */
  explicit Directory(std::string dirName);

  /**
   * @brief Default Destructor for a Directory
   */
  ~Directory();

 public:
  /**
   * @brief Verifies if a Directory contains a File with the specified name
   * @param fileName name of the File that is being searched
   * @return True if the Directory contains the File, false otherwise
   */
  File* search(const std::string& fileName);

  bool addFile(File* file);

  bool deleteFile(File* file);

  std::vector<File*> list();

  void serialize(FileStruct& fs);
};


#endif
