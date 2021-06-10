#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  HardDrive* hd = new HardDrive(1024 * 1024 * 5);
  FileSystem* fs = new FileSystem(1024*1024*5, hd);

  fs->createFile("a.txt", 0, 0, ALLOW_ALL);
  std::string prueba = "bla bla";
  for (size_t i = 0; i < 1024; i++) {
    prueba += 'b';
  }
  
  std::cout << fs->writeFile("a.txt", prueba.c_str(), prueba.length(), 0, 0) << std::endl;

  size_t s = fs->sizeOfFile("a.txt", 0, 0);
  std::vector<char> lectura(s + 1);
  lectura[s] = '\0';
  fs->readFile("a.txt", lectura.data(), s, 0, 0);

  std::cout << "Data: " << lectura.data() << std::endl;

  delete hd;
  delete fs;

  return 0;
}
