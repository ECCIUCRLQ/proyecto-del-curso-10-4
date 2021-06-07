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

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  //hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  std::vector<char> pruebaLectura;
  size_t pruebaSize = fs->sizeOfFile("/prueba", 0, 0);
  pruebaLectura.resize(pruebaSize + 10);
  std::cout << "SizeOfFile: " << pruebaSize << std::endl;
  fs->readFile("/prueba", pruebaLectura.data(), pruebaSize, 0, 0);
  std::cout << "Lectura concluida" << std::endl;
  std::cout << "El archivo 'prueba' contiene: " << pruebaLectura.data() << std::endl;

  delete hd;
  delete fs;

  return 0;
}
