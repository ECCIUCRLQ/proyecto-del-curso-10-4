#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "FileSystem.hpp"
#include "TcpServer.hpp"
#define NOMBRE_ARCHIVO "PadronPrueba.csv"

class serverPadron : public TcpServer {
 protected:
  std::string padron;
  size_t tamaño;

 public:
  serverPadron() = delete;

  /**
   * @brief DefaultConstructor for a Directory
   * @param dirName name of the Directory
   */
  explicit serverPadron();

  /**
   * @brief Default Destructor for a Directory
   */
  ~serverPadron();

 public:
  void handleClientConnection(Socket& client);
  
};


#endif
