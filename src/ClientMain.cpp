#include <iostream>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "FSClient.hpp"

int main(int argc, char const *argv[]) {
  HardDrive* hd = new HardDrive(1024 * 8);
  FileSystem* fs = new FileSystem(1024 * 8, hd);
  FSClient* client = new FSClient(*fs);

  client->shell();

  delete hd;
  delete fs;
  delete client;

  return 0;
}
