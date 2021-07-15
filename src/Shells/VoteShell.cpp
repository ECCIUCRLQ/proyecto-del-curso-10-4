#include "VoteShell.hpp"

#include <iostream>

VoteShell::VoteShell(VoteClient& voteClient) : voteClient(voteClient) {
}

VoteShell::~VoteShell() {
}

void VoteShell::shell() {
  std::string line;
  std::cout << "[Vote Client]: ";
  while (std::getline(std::cin, line)) {
    this->parse(line);
    std::cout << "[Vote Client]: ";
  }
}

void VoteShell::parse(const std::string& input) {
  std::string command;
  std::string filepath;

  // Search for the first space
  size_t pos = input.find(' ');

  // Gets the command input
  command = input.substr(0, pos);

  // Create Command
  if (command.compare(CREATE_COMMAND) == 0) {
    filepath = input.substr(pos + 1);
    this->createFile(filepath);
    return;
  }

  // Write Command
  if (command.compare(WRITE_COMMAND) == 0) {
    std::string::size_type posFin = input.find(' ', pos + 1);
    filepath = input.substr(pos + 1, posFin - pos - 1);

    std::string content = input.substr(posFin + 1);
    this->writeFile(filepath, content);

    return;
  }

  // Read File
  if (command.compare(READ_COMMAND) == 0) {
    filepath = input.substr(pos + 1);
    this->readFile(filepath);
    return;
  }

  // Delete File
  if (command.compare(DELETE_COMMAND) == 0) {
    filepath = input.substr(pos + 1);
    this->deleteFile(filepath);
    return;
  }

  // Search File
  if (command.compare(SEARCH_COMMAND) == 0) {
    filepath = input.substr(pos + 1);
    this->fileExists(filepath);
    return;
  }

  // Save Vote
  if (command.compare(VOTE_COMMAND) == 0) {
    std::string voteContent = input.substr(pos + 1);
    std::cout << "Vote content is: " << voteContent << std::endl;
    this->sendVote(voteContent);
    return;
  }

  // Print Disk
  if (command.compare(PRINT_COMMAND) == 0) {
    this->printDisk();
    return;
  }

  std::cout << "Error: invalid command" << std::endl;
  return;
}

void VoteShell::fileExists(const std::string& filepath) {
  if (this->voteClient.fileExists(filepath)) {
    std::cout << "File " << filepath << " exists" << std::endl;
  } else {
    std::cout << "File " << filepath << " does not exist" << std::endl;
  }
}

void VoteShell::createFile(const std::string& filepath) {
  if (this->voteClient.createFile(filepath)) {
    std::cout << filepath << " created successfully" << std::endl;
  } else {
    std::cout << "Could not create " << filepath << std::endl;
  }
}

void VoteShell::writeFile(const std::string& filepath, const std::string& content) {
  if (this->voteClient.writeFile(filepath, content)) {
    std::cout << filepath << " written successfully" << std::endl;
  } else {
    std::cout << "Could not write " << filepath << std::endl;
  }
}

void VoteShell::readFile(const std::string& filepath) {
  std::string content;
  if (this->voteClient.readFile(filepath, content)) {
    std::cout << content << std::endl;
  } else {
    std::cout << "Could not read " << filepath << std::endl;
  }
}

void VoteShell::deleteFile(const std::string& filepath) {
  if (this->voteClient.deleteFile(filepath)) {
    std::cout << filepath << " deleted successfully" << std::endl;
  } else {
    std::cout << "Could not delete " << filepath << std::endl;
  }
}

void VoteShell::sendVote(const std::string& voteContent) {
  if (this->voteClient.sendVote(voteContent)) {
    std::cout << "sendVote: the vote was saved successfully" << std::endl;
  } else {
    std::cout << "sendVote: could not save the vote" << std::endl;
  }
}

void VoteShell::printDisk() {
  if (this->voteClient.printDisk()) {
    this->voteClient.fs->printHD();
  } else {
    std::cout << "PrintDisk: could not print the disk" << std::endl;
  }
}
