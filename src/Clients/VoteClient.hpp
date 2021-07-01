#ifndef VOTE_CLIENT_HPP
#define VOTE_CLIENT_HPP

#include "FileSystem.hpp"
#include "FSClient.hpp"
#include "Hash.hpp"

#include <string>

#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5

#define CLASS_OPCODE 'f'
#define ID_OPCODE 'g'

class VoteClient : public FSClient {
 private:
  std::string clientClass = "";
  std::string clientID = "";

 public:
  VoteClient(FileSystem& fs, std::string& parentIp, std::string& parentPort);
  ~VoteClient();

 private:
  bool getClassAndID();

 private:
  std::string generateVoteFilename(size_t len);

 public:
  bool sendVote(const std::string& voteContent);
};


#endif
