#include "Server.hpp"

Server::Server() {
}

Server::~Server() {
}

std::string Server::readLineFromSocket(Socket& socketWithClient) {
  std::string readLine;

  // Read until null char
  socketWithClient.readLine(readLine, 0);

  return readLine;
}

void Server::sendMessage(Socket& socket, const std::string& msg) {
  socket << msg;
  socket.send();
}

void Server::sendSuccessCode(Socket& socket) {
  socket << "1";
  socket.send();
}

void Server::sendErrorMessage(Socket& socket, char errCode) {
  socket << "0";

  if (errCode) {
    socket << errCode;
  }

  socket.send();
}