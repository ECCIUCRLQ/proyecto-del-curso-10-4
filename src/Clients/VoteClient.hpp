#ifndef VOTE_CLIENT_HPP
#define VOTE_CLIENT_HPP

#include "FileSystem.hpp"
#include "FSClient.hpp"
#include "Socket.hpp"

#include <string>

#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5

#define CLASS_OPCODE 'f'
#define ID_OPCODE 'g'
#define DIST_VOTE_OPCODE 'h'

class VoteClient : public FSClient {
 private:
  std::string clientClass = "";
  std::string clientID = "";

 public:
  VoteClient() = delete;
  VoteClient(FileSystem& fs, const std::string& parentIp, const std::string& parentPort);
  virtual ~VoteClient();

 private:
  bool getClassAndID();

 private:
  std::string generateVoteFilename(size_t len);

 private:
  bool createFileNV(const std::string& filepath);

 private:
  bool distributeVote(const std::string& filepath);

 public:
  bool sendVote(const std::string& voteContent);
  bool sendVoteToClient(const std::string& filepath, const std::string& voteContent);
};


#endif
