// Copyright 2021 Equipo Tronaditas

#include "Parser.hpp"

#include <iostream>
#include <regex>

std::vector<std::string> Parser::split(const std::string &src, const char &delimiter) {
  // Result
  std::vector<std::string> matches;
  // Temporal
  std::string match;
  // get substring
  std::istringstream stream(src);

  while (std::getline(stream, match, delimiter)) {
    if (match != "") {
      // Add substring to result
      matches.push_back(match);
    }
  }

  return matches;
}

// /home/asd/ble/bli, /asd/ble, -> bli
std::string Parser::nextDirectory(const std::string &full_match, char delimiter, const std::string &currentDir) {
  std::string target;
  // split string into string vector
  std::vector<std::string> fullstring = Parser::split(full_match, delimiter);
  // search for next directory
  std::vector<std::string> current = Parser::split(currentDir, delimiter);
  
  // end of directory
  if (fullstring == current) {
    target = "";
  } else {
    size_t i = 0;
    size_t j = 0;
    
    while (fullstring.at(i) != current.at(j)) {
      i++;
    }
    
    while (j < current.size()) {
      if (fullstring.at(i) == current.at(j)) {
        i++;
        j++;
      }
    }

    target = fullstring.at(i);
  }

  return target;
}

// /prueba
std::string Parser::parentDirectory(const std::string& path, const char& delimiter) {
  std::string ret = "";

  // Get the position of the last delimeter
  size_t lastDelimiter = 0;
  for (size_t i = path.length() - 1; lastDelimiter == 0 && i > 0; --i) {
    if (path.at(i) == delimiter) {
      lastDelimiter = i;
    }
  }

  // Get the string from the start to the delimeter
  if (lastDelimiter > 0) {
    ret = path.substr(0, lastDelimiter);
  }

  return ret;
}

std::string Parser::addUntilNull(const std::string& str) {
  std::string ret = "";
  bool end = false;

  for (size_t i = 0; i < str.length() && !end; ++i) {
    char c = str.at(i);
    if (c == 0) {
      end = true;
    } else {
      ret += c;
    }
  }

  return ret;
}