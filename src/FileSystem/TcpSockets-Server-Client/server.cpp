#include "Network/TcpServer.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  TcpServer server;
  server.listenForever("8081");
  return 0;
}
