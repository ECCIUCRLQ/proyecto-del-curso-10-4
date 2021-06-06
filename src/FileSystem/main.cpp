#include <iostream>
#include <string>

#include "HardDrive.hpp"
#include "FileSystem.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*8);
  FileSystem* fs = new FileSystem(1024*8, hd);

  std::cout << fs->createFile("prueba", 0, 0, 0) << std::endl;

  std::string prueba = "";
  for (size_t i = 0; i < 5; i++) {
    if (i < 512) {
      prueba += 'a';
    } else {
      prueba += 'b';
    }
  }

  std::cout << fs->writeFile("/prueba", prueba.c_str(), prueba.length(), 0, 0) << std::endl;

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  return 0;

  fs->createFile("pruebita", 0, 0, 0);
  fs->createFile("pruebita2", 0, 0, 0);

  std::string pruebita = "Esto es una prueba";
  fs->writeFile("/pruebita", pruebita.c_str(), pruebita.length(), 0, 0);

  return 0;
}
