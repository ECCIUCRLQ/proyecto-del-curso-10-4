#include "VoteServer.hpp"

VoteServer::VoteServer(FileSystem& fs, const std::string& serverClass) :
  FSServer(fs), serverClass(serverClass) {
}

VoteServer::~VoteServer() {
  for (auto client : this->clients) {
    delete client.voteClient;
  }
}

bool VoteServer::addClient(const std::string& ipAddress, const std::string& port) {
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

void VoteServer::handleClientConnection(Socket& socketWithClient) {
  std::cout << "Server: listening..." << std::endl;
  std::string datagram = this->readLineFromSocket(socketWithClient);
  char opCode = 0;
  if (datagram.length() > 0) {
    opCode = datagram.at(0);
  }

  if (!this->handleFileSystemOps(datagram, socketWithClient)) {
    // Client Info
    if (opCode == CLIENT_INFO_OPCODE) {
      std::cout << "Client requesting info..." << std::endl;
      socketWithClient << this->getClass() << "\n" << this->getId();
      socketWithClient.send();
      return;
    }

    // Get Id operation
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
    //if (client.second.ipAddress.compare(sender) != 0) {
      // Initialize the connection
      if (!client.connected) {
        try {
          std::cout << "Connecting with " << client.ipAddress << " on port " << client.port << std::endl;
          client.voteClient = new VoteClient(*this->fileSystem, client.ipAddress, client.port);
          client.connected = true;
        } catch (std::exception& e) {
          std::cout << "Error: " << e.what() << std::endl;
        }
      }
      client.voteClient->sendVoteToClient(filepath, voteContent);
      // Toggle send to send it to half of the children
      // send != send;
    }
  //}
  return true;
}

std::string VoteServer::getClass() {
  return this->serverClass;
}

std::string VoteServer::getId() {
  return std::to_string(this->lastId++);
}
