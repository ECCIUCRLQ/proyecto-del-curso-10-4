#include "FileSystem/FileSystem.hpp"
#include "FileSystem/HardDrive.hpp"

#include "Servers/VoteServer.hpp"

#include "Utils/Parser.hpp"

#include <iostream>
#include <vector>

#define HD_SIZE 51200

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  VoteServer server(fs, "FACU_INGE");

  std::string client;
  std::vector<std::string> clientInfo;
  while (std::getline(std::cin, client)) {
    clientInfo = Parser::split(client, ':');
    if (clientInfo.size() >= 2) {
      // Add clients
      server.addClient(clientInfo[0], clientInfo[1]);
    }
  }

  server.listenForever("8081");

  return 0;
}
