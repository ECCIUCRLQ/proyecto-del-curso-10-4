#include "PadronClient.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

PadronClient::PadronClient(FileSystem& fs, const std::string& parentIp,
  const std::string& parentPort) : FSClient(fs, parentIp, parentPort) {
  this->serverIp = parentIp;
  this->serverPort = parentPort;
  char count = 0;

  // Try to get a class and ID
  while (!this->getClassAndID() && count < MAX_ATTEMPTS) {
    ++count;
  }
  
  // If it could not get a class and ID
  if (count == MAX_ATTEMPTS) {
    throw std::runtime_error("VoteClient: could not obtain a class and ID");
  }
}


PadronClient::~PadronClient() {
}

bool PadronClient::getClassAndID() {
  bool ret = true;

  // Open Socket
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  // Datagrams
  std::string datagram = std::string(1, CLIENT_INFO_OPCODE);

  // Get Class and ID separated by \n
  this->sendDatagram(socket, datagram);
  std::string clientInfo = this->readSocketResponse(socket);
  if (clientInfo.length() > 0) {
    size_t separator = clientInfo.find('\n');
    std::string sClass = clientInfo.substr(0, separator);
    std::string sID = clientInfo.substr(separator + 1);
    this->clientClass = sClass;
    this->clientID = sID;
  } else {
    ret = false;
  }

  std::cout << "Client info: " << this->clientClass << " & " << this->clientID << std::endl;
  return ret;
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
