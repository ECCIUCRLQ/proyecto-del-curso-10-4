#include <iostream>
#include <thread>

#include "FileSystem/HardDrive.hpp"
#include "FileSystem/FileSystem.hpp"
#include "Clients/VoteClient.hpp"
#include "Servers/VoteServer.hpp"
#include "Shells/VoteShell.hpp"

void initServer(FileSystem* fs) {
  VoteServer server(*fs, "URNA");
  server.listenForever("8081");
}

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  VoteClient vc(fs, "127.0.0.1", "8084");
  VoteShell vs(vc);

  std::thread server(initServer, &fs);

  vs.shell();

  server.join();

  return 0;
}
