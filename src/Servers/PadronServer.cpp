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
	padron.setVoto(carnet,0);
	  this->createFile(carnet);
	  std::string data = nombre + yaVoto + codigo + centroLoc;
	  std::vector<char> vData(data.begin(), data.end());
	  this->writeFile(carnet,vData);
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

void PadronServer::handleClientConnection(Socket& socketWithClient) {
	std::string filepath = "";
	std::string datagram = this->readLineFromSocket(socketWithClient);
	std::cout << "Comando recibido: "<< datagram << std::endl;
	char opCode = datagram.at(0);

	if(opCode == UPDATE_CODE_OPCODE){
		size_t filepathLen = this->parseWriteOp(datagram.substr(1));
	      if (filepathLen > 0) {
		std::vector<char> data;
		filepath = datagram.substr(1, filepathLen);
		data.resize(datagram.length() - filepathLen - 2);
		datagram.copy(data.data(), data.size(), filepathLen + 2);
		 
		 std::string codigo(data.begin(), data.end());
		 
		
		// Aqui hay que modificar el archivo para que se guarde el codigo correcto en el archivo, el codigo esta guardado en data
		if (this->fileExists(filepath)) {
			padron.setCodigo(filepath,codigo);
		  std::cout << "Could update code " << filepath << std::endl;
		  this->sendSuccessCode(socketWithClient);
		} else {
		  std::cout << "Could not update code " << filepath << std::endl;
		  this->sendErrorMessage(socketWithClient);
		}
	      }
	      return;
	}
	
	if (opCode == VERIFY_CODE_OPCODE){
		size_t filepathLen = this->parseWriteOp(datagram.substr(1));
	    if (filepathLen > 0) {
			std::vector<char> data;
			filepath = datagram.substr(1, filepathLen);
			data.resize(datagram.length() - filepathLen - 2);
			datagram.copy(data.data(), data.size(), filepathLen + 2);
			
			std::string codigo(data.begin(), data.end());
			
			
		// Aqui hay que verificar que en el carnet este contenido ese codigo en especifio, guardado en data
			if (padron.getCarnet(codigo) == filepath) {
			std::cout << "Could verifiy code: "<< codigo << "for: " << filepath << std::endl;
			this->sendSuccessCode(socketWithClient);
			} else {
			std::cout << "Could Not verifiy code: "<< codigo << "for: " << filepath << std::endl;
			this->sendErrorMessage(socketWithClient);
			}
		}
		return;
	}
		

	if(opCode == VERIFY_CARNET_OPCODE){
		std::string carnet = datagram.substr(1);
		if(this->fileExists(carnet)){
			this->sendSuccessCode(socketWithClient);
		}
		else{
			this->sendErrorMessage(socketWithClient);
		}
		return;
	}
			

	if(opCode == UPDATE_VOTE_OPCODE){
		std::string carnet = datagram.substr(1);
		if(this->fileExists(carnet)){
			padron.setVoto(carnet, 1);
			this->sendSuccessCode(socketWithClient);
		}
		else{
			this->sendErrorMessage(socketWithClient);
		}	
		return;
	}
	this->sendErrorMessage(socketWithClient);
	
}

std::string PadronServer::getClass() {
  return this->serverClass;
}

std::string PadronServer::getId() {
  return std::to_string(this->lastId++);
}
