#include <iostream>
#include <string>

#include "HardDrive.hpp"
#include "FileSystem.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*20);
  FileSystem* fs = new FileSystem(1024*20, hd);

  fs->createFile("prueba", 0, 0);
  //std::cout << "Prueba: " << fs->search("prueba") << std::endl;

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  delete hd;
  delete fs;

  return 0;

  std::string prueba = "";
  for (size_t i = 0; i < 512 + 512 + 512; i++) {
    if (i < 512) {
      prueba += 'a';
    } else {
      if (i < 1024) {
        prueba += 'b';
      } else {
        prueba += 'c';
      }
    }
  }
  

  // std::cout << fs->search("prueba") << std::endl;
  fs->createFile("prueba", 0, 0);
  fs->writeFile("/prueba", prueba.c_str(), prueba.length(), 0, 0);

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  return 0;
}
