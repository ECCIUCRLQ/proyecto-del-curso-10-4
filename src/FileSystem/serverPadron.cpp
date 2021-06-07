#include "serverPadron.hpp"

#include <cstring>


serverPadron::serverPadron(){
  std::ifstream archivo(NOMBRE_ARCHIVO);
  std::string linea;
  std::string prueba;
  
  
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
	this->padron = prueba;
}

serverPadron::~serverPadron() {

}

void serverPadron::handleClientConnection(Socket& client) {
	std::string hilera = "";
	client.readline(hilera);
	
	if(hilera == "solicitudDePadron"){
		client << this->padron; 
		client.send();
	}
	else{
		if (hilera == "solicitudActualizacionPadron"){
			//Aqui se le agrega al padron la nueva informacion recivida por el cliente
			
		}
	}
 
}