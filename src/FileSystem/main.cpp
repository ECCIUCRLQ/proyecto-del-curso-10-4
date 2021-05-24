#include <iostream>
#include <string>

#include "HardDrive.hpp"
#include "FileSystem.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*3);
  FileSystem* fs = new FileSystem(1024*3, hd);

  std::string prueba = "Texto de prueba";

  std::cout << fs->search("prueba") << std::endl;
  fs->createFile("prueba", 0, 0);
  fs->writeFile("/prueba", prueba.c_str(), prueba.length(), 0, 0);

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;


  delete hd;
  delete fs;

  return 0;
}
