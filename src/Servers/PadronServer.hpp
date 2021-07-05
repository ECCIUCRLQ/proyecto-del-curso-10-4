#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

// FILE SYSTEM
#include "FileSystem.hpp"
#include "FSServer.hpp"

// NETWORK
#include "NetworkAddress.hpp"
#include "Socket.hpp"

// PADRON
#include "Padron.hpp"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#define CLIENT_INFO_OPCODE  'f'
#define DIST_VOTE_OPCODE    'g'
#define NOMBRE_ARCHIVO "PadronPrueba.csv"

class PadronServer : public FSServer {
 protected:
  typedef struct {
    std::string ipAddress = "";
    std::string port = "";
    int id = 0;
    bool connected = false;
    //agregar Cliente
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