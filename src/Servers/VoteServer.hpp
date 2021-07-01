#ifndef VOTE_SERVER_HPP
#define VOTE_SERVER_HPP

// FILE SYSTEM
#include "FileSystem.hpp"
#include "FSServer.hpp"

// NETWORK
#include "NetworkAddress.hpp"
#include "Socket.hpp"

// VOTES
#include "VoteClient.hpp"

#include <map>
#include <string>
#include <vector>

#define CLASS_OPCODE 'f'
#define ID_OPCODE 'g'
#define DIST_VOTE_OPCODE 'h'

class VoteServer : public FSServer {
 protected:
  typedef struct {
    std::string ipAddress;
    int id;
    VoteClient* voteClient;
  } client_t;

 protected:
  std::string serverClass = "";
  std::map<std::string, client_t> clients;

 public:
  VoteServer(FileSystem& fs, const std::string& serverClass);
  ~VoteServer();

 public:
  bool addClient(const std::string& ipAddress, const std::string& port);

 protected:
  bool distributeVote(const std::string& filepath, const std::string& voteContent, const std::string& sender);

 protected:
  virtual void handleClientConnection(Socket& socketWithClient);
};


#endif