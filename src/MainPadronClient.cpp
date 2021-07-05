#include <iostream>
#include <thread>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "PadronServer.hpp"
#include "PadronShell.hpp"

void initServer(FileSystem* fs) {
  PadronServer server(*fs, "URNA");
  server.listenForever("8082");
}

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  PowerClient vc(fs, "127.0.0.1", "8081");
  PowerShell vs(vc);

  std::thread server(initServer, &fs);

  vs.shell();

  server.join();

  return 0;
}