#include "FSServer.hpp"
#include "HardDrive.hpp"
#include "FileSystem.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  HardDrive* hd = new HardDrive(1024 * 8);
  FileSystem* fs = new FileSystem(1024 * 8, hd);
  FSServer* server = new FSServer(*fs);

  server->listenForever("8081");

  delete server;
  delete hd;
  delete fs;

  return 0;
}
