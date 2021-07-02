#ifndef VOTE_SHELL_HPP
#define VOTE_SHELL_HPP

#include "VoteClient.hpp"

#include <string>

#define CREATE_OPCODE 'a'
#define WRITE_OPCODE  'b'
#define READ_OPCODE   'c'
#define DELETE_OPCODE 'd'
#define EXIST_OPCODE  'e'

#define CREATE_COMMAND  "create"
#define WRITE_COMMAND   "write"
#define READ_COMMAND    "read"
#define DELETE_COMMAND  "delete"
#define SEARCH_COMMAND  "search"
#define PRINT_COMMAND   "print"
#define VOTE_COMMAND    "vote"

class VoteShell {
 private:
  VoteClient& voteClient;

 public:
  VoteShell(VoteClient& voteClient);
  ~VoteShell();

 private:
  void fileExists(const std::string& filepath);
  void createFile(const std::string& filepath);
  void writeFile(const std::string& filepath, const std::string& data);
  void readFile(const std::string& filepath);
  void deleteFile(const std::string& filepath);
  void sendVote(const std::string& voteContent);
  void printDisk();

 private:
  void parse(const std::string& input);

 public:
  void shell();
};


#endif
