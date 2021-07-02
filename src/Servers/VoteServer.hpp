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

#define CLIENT_INFO_OPCODE  'f'
#define DIST_VOTE_OPCODE    'g'

class VoteServer : public FSServer {
 protected:
  typedef struct {
    std::string ipAddress = "";
    std::string port = "";
    int id = 0;
    bool connected = false;
    VoteClient* voteClient = nullptr;
  } client_t;

 protected:
  std::string serverClass = "";
  std::vector<client_t> clients;
  //std::map<int, client_t> clients;
  size_t lastId = 0;

 public:
  VoteServer(FileSystem& fs, const std::string& serverClass);
  ~VoteServer();

 public:
  bool addClient(const std::string& ipAddress, const std::string& port);

 protected:
  std::string getClass();
  std::string getId();
  bool distributeVote(const std::string& filepath, const std::string& voteContent, const std::string& sender);

 protected:
  virtual void handleClientConnection(Socket& socketWithClient);
};


#endif