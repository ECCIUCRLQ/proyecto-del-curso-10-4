#ifndef VOTE_CLIENT_HPP
#define VOTE_CLIENT_HPP

// CLIENTS
#include "FSClient.hpp"

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"

// NETWORK
#include "Network/Socket.hpp"
#include "Network/TcpClient.hpp"

#include <string>

#define MAX_ATTEMPTS 3
#define RANDOM_FILENAME_LEN 5

#define CLIENT_INFO_OPCODE  'f'
#define DIST_VOTE_OPCODE    'g'

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

 public:
  std::string generateVoteFilename(size_t len);

 public:
  bool createFileLocal(const std::string& filepath);
  bool writeFileLocal(const std::string& filepath, const std::string& data);

 public:
  bool distributeVote(const std::string& filepath);

 public:
  bool sendVote(const std::string& voteContent);
  bool sendVoteToClient(const std::string& filepath, const std::string& voteContent);
};


#endif
