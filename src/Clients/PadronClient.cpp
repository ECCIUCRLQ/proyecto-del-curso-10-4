#include "PadronClient.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

PadronClient::PadronClient(const std::string& parentIp,
  const std::string& parentPort) : Client() {
  this->serverIp = parentIp;
  this->serverPort = parentPort;
}

PadronClient::~PadronClient() {
}

std::string PadronClient::sendReceiveDatagram(std::string opCode, const std::string& carnet, const std::string& other) {
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = opCode + carnet;
  if (other.length() > 0) {
    datagram += " " + other;
  }
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);

  return response;
}

bool PadronClient::verifyCarnet(const std::string& carnet){
  bool existeVotante = false;
  std::string response = this->sendReceiveDatagram(VERIFY_CARNET_OPCODE, carnet);

	if (response.length() > 0 && response.at(0) == '1') {
		existeVotante = true;
	}

  return existeVotante;
}

bool PadronClient::updateCode(const std::string& carnet, std::string code){
  bool success = false;
  std::string response = this->sendReceiveDatagram(UPDATE_CODE_OPCODE, carnet, code);

  if (response.length() > 0 && response.at(0) == '1') {
    success = true;
  }

  return success;
}

bool PadronClient::verifyCode(const std::string& carnet, std::string codigo){
  bool match = false;
  std::string response = this->sendReceiveDatagram(VERIFY_CODE_OPCODE, carnet, codigo);

	if (response.length() > 0 && response.at(0) == '1') {
		match = true;
	}

	return match;
}

bool PadronClient::verifyVote(const std::string& carnet) {
  bool voted = false;
  std::string response = this->sendReceiveDatagram(VERIFY_VOTE_OPCODE, carnet);

  if (response.length() > 0 && response.at(0) == '1') {
		voted = true;
	}

  return voted;
}

bool PadronClient::updateVote(const std::string& carnet){
  bool success = false;
  std::string response = this->sendReceiveDatagram(UPDATE_VOTE_OPCODE, carnet);

  if(response.length() > 0 && response.at(0) == '1'){
	  success = true;
  }

  return success;
}

bool PadronClient::verifyCentroVotacion(const std::string& carnet, const std::string& centro) {
  bool success = false;
  std::string response = this->sendReceiveDatagram(GET_CENTRO_OPCODE, carnet, centro);

  if (response.length() > 0 && response.at(0) == '1') {
	  success = true;
  }

  return success;
}

std::string PadronClient::getCentroVotacion(const std::string& carnet) {
  std::string centro = "Centro de Votación no encontrado";
  std::string response = this->sendReceiveDatagram(GET_CENTRO_OPCODE, carnet);

  if (response.length() > 0 && response.at(0) == '1') {
	  response = response.substr(1);
  }

  return response;
}

std::string PadronClient::getNombreCompleto(const std::string& carnet) {
  std::string nombre = "Usuario no encontrado";
  std::string response = this->sendReceiveDatagram(GET_NOMBRE_OPCODE, carnet);

  if (response.length() > 0 && response.at(0) == '1') {
	  response = response.substr(1);
  }

  return response;
}

void PadronClient::printPadron() {
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());
  std::string datagram = "print";
  this->sendDatagram(socket, datagram);
  socket.close();
  return;
}
