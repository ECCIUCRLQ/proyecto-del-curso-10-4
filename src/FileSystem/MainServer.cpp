#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "FileSystemServer.hpp"
#define NOMBRE_ARCHIVO "PadronPrueba.csv"


int main(int argc, char* argv[]) {
  HardDrive* hd = new HardDrive(1024*8);
  FileSystem* fs = new FileSystem(1024*8, hd);
  FileSystemServer* fss = new FileSystemServer(fs);
  std::ifstream archivo(NOMBRE_ARCHIVO);
  std::string linea;
  char delimitador = ',';
  getline(archivo, linea);
  fs->createFile("prueba", 0, 0,'O');
  std::string prueba = "";
  while (getline(archivo, linea)) {
  	std::stringstream stream(linea);
  	std::string carnet, apellido1, apellido2, nombre, voto;
  	getline(stream, carnet, delimitador);
  	getline(stream, apellido1, delimitador);
  	getline(stream, apellido2, delimitador);
  	getline(stream, nombre, delimitador);
  	getline(stream, voto, delimitador);
  	prueba+=carnet;
  	std::cout << carnet;
  	prueba+=apellido1;
  	std::cout << apellido1;
  	prueba+=apellido2;
  	std::cout << apellido2;
  	prueba+=nombre;
  	std::cout << nombre;
  	prueba+=voto;
  	std::cout << voto;
  	
  }

  
  
  fs->writeFile("/prueba", prueba.c_str(), prueba.length(), 0, 0);
  std::cout << prueba;
  fs->createFile("pruebita", 0, 0,'O');
  fs->createFile("pruebita2", 0, 0,'O');

  std::cout << "--- BEGINNING OF DISK ---" << std::endl;
  hd->print();
  std::cout << "--- END OF DISK ---" << std::endl;

  fss->receiveFile("/prueba",prueba,0,0);

  return 0;
}
