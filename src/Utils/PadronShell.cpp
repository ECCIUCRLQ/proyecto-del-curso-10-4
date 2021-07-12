#include "PadronShell.hpp"

#include <iostream>

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
  std::string command;
  std::string filepath;

  // Search for the first space
  size_t pos = input.find(' ');

  // Gets the command input
  command = input.substr(0, pos);

  // Create Command
 
  // Update Code
  if (command.compare(UPDATECODE_COMMAND) == 0) {
    std::string carnet = input.substr(pos + 1,pos+7);
   // std::string code = input.substr(pos+9, pos+29);
    std::string hasheado = "vm5960sl6059ot06pdof";
    std::cout << "Your Carnet : " << carnet << " associated with verificaition code:"<<hasheado<<std::endl;
    this->updateCode(carnet, hasheado);
    return;
  }
  // Verify Code
  if (command.compare(VERIFYCODE_COMMAND) == 0) {
    std::string carnet = input.substr(pos + 1,pos+7);
    //std::string code = input.substr(pos+9, pos+29);
    std::string hasheado = "vm5960sl6059ot06pdof";
    std::cout << "Your Carnet : " << carnet << " associated with verificaition code:"<<hasheado<<std::endl;
    this->verifyCode(carnet, hasheado);
    return;
  }
  if (command.compare(VERIFYCARNET_COMMAND) == 0) {
    std::string carnet = input.substr(pos + 1,pos+7);
    std::cout << "Your Carnet : " << carnet;
    this->verifyCarnet(carnet);
    return;
  }
    if (command.compare(UPDATEVOTE_COMMAND) == 0) {
    std::string carnet = input.substr(pos + 1,pos+7);
    std::cout << "Your Carnet : " << carnet;
    this->updateVote(carnet);
    return;
  }
    if (command.compare(PRINT_COMMAND) == 0) {
      this->printDisk();
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
void PadronShell::verifyCarnet(const std::string& filepath) {
  if (this->padronClient.verifyCarnet(filepath)) {
    std::cout << "verifyCarnet: valid code" << std::endl;
  } else {
    std::cout << "verifyCarnet: invalid code" << std::endl;
  }
}
void PadronShell::updateVote(const std::string& filepath) {
  if (this->padronClient.updateVote(filepath)) {
    std::cout << "updateVote: vote updated successfully" << std::endl;
  } else {
    std::cout << "updateVote: unsuccessful update" << std::endl;
  }
}

void PadronShell::printDisk() {
  if (this->padronClient.printDisk()) {
    this->padronClient.fs->printHD();
  } else {
    std::cout << "PrintDisk: could not print the disk" << std::endl;
  }
}
