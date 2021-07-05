#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "../Votacion/Padron.hpp"
#include "../Network/Socket.hpp"
#include "../Network/TcpServer.hpp"

#define NOMBRE_ARCHIVO "PadronPrueba.csv"

class serverPadron : public TcpServer {
 private:
  Padron padron;
 public:
  serverPadron();
  ~serverPadron();

 public:
  void handleClientConnection(Socket& client);
};


#endif
