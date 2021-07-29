// Copyright 2021 Equipo Tronaditas

#ifndef FS_UTILS_HPP
#define FS_UTILS_HPP

#include <string>
#include <vector>

class Parser {
 public:
  /**
   * @brief Splits a string using a defined char as a delimeter
   * @param src String to be split
   * @param delimeter Delimeter to use for splitting the string
   * @return An std::vector containing each portion of the split string
   */
  static std::vector<std::string> split(const std::string& src, const char& delimiter);

  // Add doc
  static std::string nextDirectory(const std::string& full_match, char delimiter,const std::string& currentDir);
  
  // Add doc
  static std::string parentDirectory(const std::string& path, const char& delimiter);

  // Add doc
  static std::string addUntilNull(const std::string& str);
};


#endif // UTILS_H
