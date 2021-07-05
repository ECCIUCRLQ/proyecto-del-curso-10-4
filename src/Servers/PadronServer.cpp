#include "PadronServer.hpp"
#include <cstring>
#define NOMBRE_ARCHIVO "PadronPrueba.csv"

PadronServer::PadronServer(FileSystem& fs, const std::string& serverClass) :
  FSServer(fs), serverClass(serverClass) {
  
  std::ifstream archivo(NOMBRE_ARCHIVO);
  std::string linea;
  char delimitador = ',';// esto se debe cambiar segun el delimitador que presenta el padron
    
  getline(archivo, linea);
  while (getline(archivo, linea))
  {

    std::stringstream stream(linea); // Convertir la cadena a un stream
    std::string carnet, nombre, apellido1, apellido2, yaVoto, codigo, centroLoc;
    // Extraer todos los valores de esa fila- todos estos valores se cambian segun los datos que se necesitan para el padron
    getline(stream, carnet, delimitador);
    getline(stream, nombre, delimitador);
    getline(stream, apellido1, delimitador);
    getline(stream, apellido2, delimitador);
    getline(stream, yaVoto, delimitador);
    getline(stream, codigo, delimitador);
    getline(stream, centroLoc, delimitador);
    // Imprimir

	padron.agregarVotante(carnet);
	nombre = nombre + apellido1 + apellido2;
	padron.setNombre(carnet,nombre);
	padron.setCodigo(carnet,codigo);
	padron.setVoto(carnet,stoi(yaVoto));
	  
	  this->createFile(carnet);
	  std:string data = nombre + voto + codigo + centroLoc;
	  std::vector<char> vData(data.begin(), data.end());
	  this->writeFile(carnet,v);
    // no es necesario imprimir los valores sino guardarlos 
  }
  archivo.close();

}

PadronServer::~PadronServer() {
  for (auto client : this->clients) {
    delete client.padronClient;
  }
}

bool PadronServer::addClient(const std::string& ipAddress, const std::string& port) {
  bool ret = false;

  //if (this->clients.find(ipAddress) == this->clients.end()) {
    // Create a new struct for the client
    client_t newClient;
    newClient.ipAddress = ipAddress;
    newClient.port = port;
    newClient.id = this->clients.size() + 1;
    newClient.connected = false;

    // Insert the new client to the array and associates it with its IP Address
    // TODO(change key back to IP after testing) ¿also use map?
    this->clients.push_back(newClient);
    ret = true;
  //}

  return ret;
}

void PadronServer::handleClientConnection(Socket& client) {
	std::string hilera = "";
	client.readLine(hilera);
	std::cout << "Comando recibido: "<< hilera << std::endl;
	char opCode = hilera.at(0);

	if(opCode == 'a'){
		std::string carnet = "";
		for(int i = 1; i<hilera.length();++i){
			carnet+= hilera.at(i);
		}
		padron.agregarVotante(carnet);
		padron.setCodigo(carnet,rand()%600000 +1);
		hilera = "Actualizado codigo en padron para carnet:";
		hilera += carnet;
		client << hilera; 
		client.send();
	}
	else{
		if (opCode == 'b'){
			std::string codigo = "";
			for(int i = 1; i<hilera.length();++i){
			codigo+= hilera.at(i);
			}
			//Aqui se le agrega al padron la nueva informacion recivida por el cliente
			hilera = "Carnet asociado a codigo";
			hilera += codigo + ": " + padron.getCarnet(codigo); ;
			client << hilera;
			client.send();
		}
		else{

			if(opCode == 'c'){
				std::string carnet = "";
				for(int i = 1; i<hilera.length();++i){
					carnet+= hilera.at(i);
				}
				padron.setVoto(carnet,1);
				hilera = "Actualizado voto en padron para carnet:";
				hilera += carnet;
				client << hilera; 
				client.send();

			}
			else{

				if(opCode == 'd'){
					std::string carnet = "";
					for(int i = 1; i<hilera.length();++i){
						carnet+= hilera.at(i);
					}
					hilera = "Votante con carnet: ";
					hilera += carnet + "  Voto: " + std::to_string(padron.getVoto(carnet));
					client << hilera; 
					client.send();

				}
				else{
					std::string carnet = "";
					for(int i = 1; i<hilera.length();++i){
						carnet+= hilera.at(i);
					}
					hilera = "Codigo asociado a carnet ";
					hilera += carnet + ": " + padron.getCodigo(carnet);
					client << hilera;
					client.send();



				}
			}
		
		}
	}
 
}

std::string PadronServer::getClass() {
  return this->serverClass;
}

std::string PadronServer::getId() {
  return std::to_string(this->lastId++);
}
