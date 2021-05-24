#include "HardDrive.hpp"
#include "FileSystem.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*1024*30);
  FileSystem* fs = new FileSystem(1024*1024*30, hd);

  delete hd;
  delete fs;

  return 0;
}
