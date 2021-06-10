#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Padron.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"

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
