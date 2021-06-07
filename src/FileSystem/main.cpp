#include <iostream>
#include <string>
#include <vector>

#include "HardDrive.hpp"
#include "FileSystem.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*8);
  FileSystem* fs = new FileSystem(1024*8, hd);

  fs->createFile("prueba", 0, 0, 0);

  std::string prueba = "";
  for (size_t i = 0; i < 1024; i++) {
    if (i < 512) {
      prueba += 'a';
    } else {
      prueba += 'b';
    }
  }

  fs->writeFile("/prueba", prueba.c_str(), prueba.length(), 0, 0);

  std::string prueba2 = "abcdef";
  fs->createFile("prueba2", 0, 0, 0);
  fs->writeFile("/prueba2", prueba2.c_str(), prueba2.length(), 0, 0);
  fs->printBitmap();

  std::string prueba3 = "abcdefghijk";
  fs->createFile("pruebita", 0, 0, 0);
  fs->writeFile("/pruebita", prueba3.c_str(), prueba3.length(), 0, 0);

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  delete hd;
  delete fs;

  return 0;
}
