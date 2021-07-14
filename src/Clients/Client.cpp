#include "Client.hpp"

Client::Client() {
}

Client::~Client() {
}

void Client::sendDatagram(Socket& socket, const std::string& datagram) {
  socket << datagram;
  socket.send();
}

std::string Client::readSocketResponse(Socket& socket) {
  std::string ret;
  socket.readLine(ret, 0);
  return ret;
}
