#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Network/Socket.hpp"

class Client {
 protected:
  std::string serverIp = "";
  std::string serverPort = "";

 public:
  Client();
  virtual ~Client();

 protected:
  virtual void sendDatagram(Socket& socket, const std::string& datagram);
  virtual std::string readSocketResponse(Socket& socket);
};


#endif
