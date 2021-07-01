#include "VoteServer.hpp"

VoteServer::VoteServer(FileSystem& fs, const std::string& serverClass) :
  FSServer(fs), serverClass(serverClass) {
}

VoteServer::~VoteServer() {
  // TODO(any): clean clients
}

bool VoteServer::addClient(const std::string& ipAddress, const std::string& port) {
  bool ret = false;

  if (this->clients.find(ipAddress) == this->clients.end()) {
    // Create a new struct for the client
    client_t newClient;
    newClient.ipAddress = ipAddress;
    newClient.id = this->clients.size() + 1;
    newClient.voteClient = new VoteClient(*this->fileSystem, ipAddress, port);

    // Insert the new client to the array and associates it with its IP Address
    this->clients.insert(std::pair<std::string, client_t>(ipAddress, newClient));
    ret = true;
  }

  return ret;
}

void VoteServer::handleClientConnection(Socket& socketWithClient) {
  std::cout << "Server: listening..." << std::endl;
  std::string datagram = this->readLineFromSocket(socketWithClient);
  char opCode = 0;
  if (datagram.length() > 0) {
    opCode = datagram.at(0);
  }

  if (!this->handleFileSystemOps(datagram, socketWithClient)) {
    // Distribute vote
    if (opCode == DIST_VOTE_OPCODE) {
      // Filepath
      std::string filepath = datagram.substr(1);

      // Vote content
      std::string voteContent;
      this->readFile(filepath, voteContent);

      // Sender IP Address
      std::string sender = socketWithClient.getNetworkAddress().getIP();

      if (this->distributeVote(filepath, voteContent, sender)) {
        std::cout << "Distribute: could distribute the file " << filepath << std::endl;
        this->sendSuccessCode(socketWithClient);
      } else {
        std::cout << "Distribute: could not distribute the file " << filepath << std::endl;
        this->sendErrorMessage(socketWithClient);
      }
      return;

      std::cout << "Error: opcode not supported" << std::endl;
      this->sendErrorMessage(socketWithClient);
    }
  }

  return;
}

bool VoteServer::distributeVote(const std::string& filepath, const std::string& voteContent, const std::string& sender) {
  bool send = true;
  for (auto client : this->clients) {
    if (client.second.ipAddress.compare(sender) != 0) {
      client.second.voteClient->sendVoteToClient(filepath, voteContent);
    }
  }
  return true;
}
