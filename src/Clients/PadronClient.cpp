#include "PadronClient.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

PadronClient::PadronClient(const std::string& parentIp,
  const std::string& parentPort) : Client() {
  this->serverIp = parentIp;
  this->serverPort = parentPort;
}

PadronClient::~PadronClient() {
}

bool PadronClient::updateCode(const std::string& filepath, std::string codigo){
  bool success = false;
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = UPDATE_CODE_OPCODE + filepath + "\n" + codigo;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);

  if(response.at(0) == '1'){
    success = true;
  }

  return success;
}

bool PadronClient::verifyCode(const std::string& filepath, std::string codigo){
  bool match = false;
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = VERIFY_CODE_OPCODE + filepath + "\n" + codigo;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
	if(response.at(0) == '1'){
		match = true;
	}

	return match;
}

bool PadronClient::verifyCarnet(const std::string& filepath){
  bool existeVotante = false;
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::cout << "Comando enviado pre: "<< filepath << std::endl;
  std::string datagram = VERIFY_CARNET_OPCODE + filepath;
  std::cout << "Comando enviado: "<< datagram << std::endl;
  this->sendDatagram(socket, datagram);
  std::string response = this->readSocketResponse(socket);
	if(response.at(0) == '1'){
		existeVotante = true;
	}

  return existeVotante;
}

bool PadronClient::updateVote(const std::string& filepath){
  bool success = false;
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = UPDATE_VOTE_OPCODE + filepath;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);

  if(response.at(0) == '1'){
	  success = true;
  }

  return success;	
}

bool PadronClient::printDisk() {
  std::cout << "UNO" <<std::endl;
  bool success = false;
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());
  std::cout << "DOS" << std::endl;
  std::string datagram = "z";
  std::cout << datagram << std::endl;
  this->sendDatagram(socket, datagram);
  std::string response = this->readSocketResponse(socket);

  if(response.at(0) == '1'){
    success = true;
  
  }

  return success; 
}
