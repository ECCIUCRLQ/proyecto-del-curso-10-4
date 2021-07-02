#include <iostream>
#include <thread>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "VoteClient.hpp"
#include "VoteServer.hpp"
#include "VoteShell.hpp"

void initServer(FileSystem* fs) {
  VoteServer server(*fs, "URNA");
  server.listenForever("8083");
}

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  VoteClient vc(fs, "127.0.0.1", "8081");
  VoteShell vs(vc);

  std::thread server(initServer, &fs);

  vs.shell();

  server.join();

  return 0;
}
