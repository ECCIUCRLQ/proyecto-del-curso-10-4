#include "Padron.hpp"
#include <iostream>
#include <thread>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "PadronServer.hpp"

void initServer(FileSystem* fs) {
  PadronServer server(*fs, "URNA");
  server.listenForever("8082");
}

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  initServer(&fs);

  return 0;
}
