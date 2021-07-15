#include "Servers/VoteServer.hpp"
#include "FileSystem/HardDrive.hpp"
#include "FileSystem/FileSystem.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  VoteServer server(fs, "FACU_INGE");

  // Add clients
  server.addClient("127.0.0.1", "8082");
  server.addClient("127.0.0.1", "8083");

  server.listenForever("8081");

  return 0;
}
