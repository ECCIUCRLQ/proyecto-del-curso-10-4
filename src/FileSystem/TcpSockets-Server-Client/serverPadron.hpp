#ifndef SERVER_PADRON_HPP
#define SERVER_PADRON_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
//#include "FileSystem.hpp"
#include "TcpServer.hpp"
#define NOMBRE_ARCHIVO "PadronPrueba.csv"

class serverPadron : public TcpServer {
 protected:
  std::string padron;
  size_t tamano;

 public:
  serverPadron();

  /**
   * @brief Default Destructor for a Directory
   */
  ~serverPadron();

 public:
  void handleClientConnection(Socket& client);
  
};


#endif
