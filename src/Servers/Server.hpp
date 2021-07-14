#ifndef SERVER_HPP
#define SERVER_HPP

// NETWORK
#include "Network/Socket.hpp"
#include "Network/TcpServer.hpp"

#include <string>

class Server : public TcpServer {
 public:
  Server();
  ~Server();

 protected:
  void sendSuccessCode(Socket& socket);
  void sendErrorMessage(Socket& socket, char errCode = 0);

 protected:
  std::string readLineFromSocket(Socket& socketWithClient);
};


#endif
