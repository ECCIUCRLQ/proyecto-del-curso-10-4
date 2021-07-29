#include "PadronShell.hpp"

#include <iostream>
#include <vector>

PadronShell::PadronShell(PadronClient& padronClient) : padronClient(padronClient) {
}

PadronShell::~PadronShell() {
}

void PadronShell::shell() {
  std::string line;
  std::cout << "[Padron Client]: ";
  while (std::getline(std::cin, line)) {
    this->parse(line);
    std::cout << "[Padron Client]: ";
  }
}

void PadronShell::parse(const std::string& input) {
  std::vector<std::string> commandParts = Parser::split(input, ' ');
  
  // Verify print command first
  // Print Padron
  if (input.compare(PRINT_COMMAND) == 0) {
    this->printPadron();
    return;
  }

  // Exit if no parts were read
  if (commandParts.size() < 2) {
    return;
  }
  std::string command = commandParts[0];
  std::string carnet = commandParts[1];

  // Verify Carnet
  if (command.compare(VERIFYCARNET_COMMAND) == 0) {
    std::string carnet = commandParts[1];
    this->verifyCarnet(carnet);
    return;
  }
 
  // Update Code
  if (command.compare(UPDATECODE_COMMAND) == 0) {
    if (commandParts.size() >= 3) {
      std::string codigo = commandParts[2];
      this->updateCode(carnet, codigo);
    }
    return;
  }

  // Verify Code
  if (command.compare(VERIFYCODE_COMMAND) == 0) {
    if (commandParts.size() >= 3) {
      std::string codigo = commandParts[2];
      this->verifyCode(carnet, codigo);
    }
    return;
  }

  // Verify Vote
  if (command.compare(VERIFYVOTE_COMMAND) == 0) {
    this->verifyVote(carnet);
    return;
  }

  // Update Vote
  if (command.compare(UPDATEVOTE_COMMAND) == 0) {
    this->updateVote(carnet);
    return;
  }

  // Get vote centre
  if (command.compare(GETCENTRO_COMMAND) == 0) {
    this->getCentro(carnet);
    return;
  }

  // Get name
  if (command.compare(GETNAME_COMMAND) == 0) {
    this->getName(carnet);
    return;
  }

  std::cout << "Error: invalid command" << std::endl;
  return;
}

void PadronShell::updateCode(const std::string& filepath,std::string codigo) {
  if (this->padronClient.updateCode(filepath,codigo)) {
    std::cout << "updateCode: code updated in padron successfully" << std::endl;
  } else {
    std::cout << "updateCode: not updated successfully" << std::endl;
  }
}

void PadronShell::verifyCode(const std::string& filepath,std::string codigo) {
  if (this->padronClient.verifyCode(filepath,codigo)) {
    std::cout << "verifyCode: code verified sucessfully" << std::endl;
  } else {
    std::cout << "verifyCode: invalid code" << std::endl;
  }
}

void PadronShell::verifyCarnet(const std::string& carnet) {
  if (this->padronClient.verifyCarnet(carnet)) {
    std::cout << "verifyCarnet: valid carnet" << std::endl;
  } else {
    std::cout << "verifyCarnet: invalid carnet" << std::endl;
  }
}

void PadronShell::verifyVote(const std::string& carnet) {
  if (this->padronClient.verifyVote(carnet)) {
    std::cout << "verifyVote: you have voted already" << std::endl;
  } else {
    std::cout << "verifyVote: you have not voted" << std::endl;
  }
}

void PadronShell::updateVote(const std::string& carnet) {
  if (this->padronClient.updateVote(carnet)) {
    std::cout << "updateVote: vote updated successfully" << std::endl;
  } else {
    std::cout << "updateVote: unsuccessful update" << std::endl;
  }
}

void PadronShell::getCentro(const std::string& carnet) {
  std::string centro = this->padronClient.getCentroVotacion(carnet);
  if (centro.length() > 0) {
    std::cout << "The vote centre for " << carnet << " is " << centro << std::endl;;
  } else {
    std::cout << "getCentro: could not get the vote centre" << std::endl;
  }
}

void PadronShell::getName(const std::string& carnet) {
  std::string name = this->padronClient.getNombreCompleto(carnet);
  if (name.length() > 0) {
    std::cout << "The name for " << carnet << " is " << name << std::endl;
  } else {
    std::cout << "getName: could not get the name for " << carnet << std::endl;
  }
}

void PadronShell::printPadron() {
  std::cout << "Shell print" << std::endl;
  this->padronClient.printPadron();
}
