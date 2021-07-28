#include "PadronServer.hpp"

#include <iostream>
#include <vector>
#include <sstream>


PadronServer::PadronServer(PadronManager& padron) : Server(), padron(&padron) {
  std::cout << "Server started..." << std::endl;
}

PadronServer::~PadronServer() {
}

std::string PadronServer::carnetValido(const std::string& carnet) {
  std::string ret = "0";
  if (this->padron->votanteExiste(carnet)) {
    ret = "1";
  }
  std::stringstream ss (ret);
  int x = 0;
  ss >> x;
  this->logger->log("carnetValido",carnet,x);
  return ret;
}

std::string PadronServer::codigoValido(const std::string& carnet, const std::string& codigo) {
  std::string ret = "0";
  if (this->padron->votanteExiste(carnet)) {
    if (this->padron->getCodigo(carnet).compare(codigo) == 0) {
      ret = "1";
    }
  }
  std::stringstream ss (ret);
  int x = 0;
  ss >> x;
  this->logger->log("codigoValido", codigo, x);
  return ret;
}

std::string PadronServer::getNombreCompleto(const std::string& carnet) {
  std::string nombreCompleto = this->padron->getNombreCompleto(carnet);

  if (nombreCompleto.length() > 0) {
    nombreCompleto.insert(0, "1");
    this->logger->log("nombreCompleto", nombreCompleto, 1 );
  } else {
    this->logger->log("nombreCompleto", nombreCompleto, 0);
    nombreCompleto = "0";
  }
  return nombreCompleto;
}

std::string PadronServer::getCentroVotacion(const std::string& carnet) {
  std::string centro = this->padron->getCentroVotacion(carnet);
  
  if (centro.length() > 0) {
    centro.insert(0, "1");
    this->logger->log("centroVotacion", carnet, 1 );
  } else {
    centro = "0";
    this->logger->log("centroVotacion", carnet, 0);
  }
  return centro;
}

std::string PadronServer::getHaVotado(const std::string& carnet) {
  std::string ret = "0";
  if (this->padron->getHaVotado(carnet)) {
    ret = "1";
  }
  std::stringstream ss (ret);
  int x = 0;
  ss >> x;
  this->logger->log(" confirmando que haVotado", carnet, x);
  return ret;
}

std::string PadronServer::setCodigo(const std::string& carnet, const std::string& codigo) {
  std::string ret = "0";
  if (this->padron->setCodigo(carnet, codigo)) {
    ret = "1";
  }
  std::stringstream ss (ret);
  int x = 0;
  ss >> x;
  this->logger->log("setCodigo", carnet + " "+ codigo, x);
  return ret;
}

std::string PadronServer::setHaVotado(const std::string& carnet) {
  std::string ret = "0";
  if (this->padron->setHaVotado(carnet)) {
    ret = "1";
  }
  std::stringstream ss (ret);
  int x = 0;
  ss >> x;
  this->logger->log("actualizando haVotado", carnet, x);
  return ret;
}

void PadronServer::handleClientConnection(Socket& socket) {
  std::string datagram = this->readLineFromSocket(socket);
  char opCode = datagram.at(0);

  // Verify carnet
  if (opCode == VERIFY_CARNET_OPCODE) {
    std::string carnet = datagram.substr(1);
    datagram = this->carnetValido(carnet);
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Get Centro de Votación
  if (opCode == GET_CENTRO_OPCODE) {
    std::string carnet = datagram.substr(1);
    datagram = this->getCentroVotacion(carnet);
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Get Nombre Completo
  if (opCode == GET_NOMBRE_OPCODE) {
    std::string carnet = datagram.substr(1);
    datagram = this->getNombreCompleto(carnet);
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Ha Votado
  if (opCode == VERIFY_VOTE_OPCODE) {
    std::string carnet = datagram.substr(1);
    datagram = this->getHaVotado(carnet);
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Update Code
  if (opCode == UPDATE_CODE_OPCODE) {
    datagram = datagram.substr(1);
    std::vector<std::string> parts = Parser::split(datagram, ' ');
    if (parts.size() >= 2) {
      datagram = this->setCodigo(parts[0], parts[1]);
    } else {
      datagram = "0";
    }
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Verify Code
  if (opCode == VERIFY_CODE_OPCODE) {
    datagram = datagram.substr(1);
    std::vector<std::string> parts = Parser::split(datagram, ' ');
    if (parts.size() >= 2) {
      datagram = this->codigoValido(parts[0], parts[1]);
    } else {
      datagram = "0";
    }
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  // Set HaVotado
  if (opCode == UPDATE_VOTE_OPCODE) {
    std::string carnet = datagram.substr(1);
    datagram = this->setHaVotado(carnet);
    this->sendMessage(socket, datagram);
    socket.close();
    return;
  }

  this->sendErrorMessage(socket);
  socket.close();
  return;
}
