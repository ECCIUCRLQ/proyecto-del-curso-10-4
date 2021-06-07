#include <iostream>
#include <string>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "FileSystemClient.hpp"

int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*8);
  FileSystem* fs = new FileSystem(1024*8, hd);
  FileSystemClient* fsc = new FileSystemClient(fs);
  fs->createFile("prueba", 0, 0,'O');


  std::string voto = "abdl283";
  
 
  
  fs->writeFile("/prueba", voto.c_str(), voto.length(), 0, 0);
 
  fs->createFile("pruebita", 0, 0,'O');
 

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  std::string recivido = fsc->sendSocket();
  std::cout << recivido << std::endl;
  std::string recivido = fsc->sendSocket();
  std::cout << recivido << std::endl;
  std::string recivido = fsc->sendSocket();
  std::cout << recivido << std::endl;

  return 0;
}
