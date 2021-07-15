#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

// CLIENTS
#include "Clients/PadronClient.hpp"

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"

// NETWORK
#include "Network/Socket.hpp"

// SERVERS
#include "FSServer.hpp"

// VOTACION
#include "Votacion/Padron.hpp"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#define UPDATE_CODE_OPCODE 'h'
#define UPDATE_VOTE_OPCODE 'i'
#define VERIFY_CODE_OPCODE 'j'
#define VERIFY_CARNET_OPCODE 'k'
#define CLIEN_INFO_OPCODE  'f'
#define DIST_VOTE_OPCODE    'g'
#define NOMBRE_ARCHIVO "PadronPrueba.csv"

class PadronServer : public FSServer {
 protected:
  typedef struct {
    std::string ipAddress = "";
    std::string port = "";
    int id = 0;
    bool connected = false;
    PadronClient* padronClient;
  } client_t;

 protected:
  Padron padron;
  std::string serverClass = "";
  std::vector<client_t> clients;
  //std::map<int, client_t> clients;
  size_t lastId = 0;

 public:
  PadronServer(FileSystem& fs, const std::string& serverClass);
  ~PadronServer();

 public:
  bool addClient(const std::string& ipAddress, const std::string& port);

 protected:
  std::string getClass();
  std::string getId();

 protected:
  virtual void handleClientConnection(Socket& socketWithClient);
};


#endif
