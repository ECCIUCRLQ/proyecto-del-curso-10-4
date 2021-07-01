#include "VoteClient.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

VoteClient::VoteClient(FileSystem& fs, std::string& parentIp,
  std::string& parentPort) : FSClient(fs, parentIp, parentPort) {
  char count = 0;

  // Try to get a class and ID
  while (!this->getClassAndID() && count < MAX_ATTEMPTS) {
    ++count;
  }
  
  // If it could not get a class and ID 
  throw std::runtime_error("VoteClient: could not obtain a class and ID");
}

VoteClient::~VoteClient() {
}

bool VoteClient::getClassAndID() {
  bool ret = true;

  // Open Socket
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  // Datagrams
  std::string classDatagram = "";
  std::string idDatagram = "";
  classDatagram += CLASS_OPCODE;
  idDatagram += ID_OPCODE;

  // Get Class
  this->sendDatagram(socket, classDatagram);
  this->clientClass = this->readSocketResponse(socket);
  if (this->clientClass.length() == 0) {
    ret = false;
  }

  // Get ID
  this->sendDatagram(socket, idDatagram);
  this->clientID = this->readSocketResponse(socket);
  if (this->clientID.length() == 0) {
    ret = false;
  }

  return ret;
}

std::string VoteClient::generateVoteFilename(size_t len) {
  // Class and ID
  std::string filename = this->clientClass;
  filename += this->clientID + "_";

  // Random seed
  ::srand((unsigned) ::time(0));

  // Get n random chars
  for (size_t i = 0; i < len; ++i) {
    int number = (::rand() % 25) + 97;
    filename += (char) number;
  }
  
  return filename;
}

bool VoteClient::sendVote(const std::string& voteContent) {
  // Generate a filepath for the vote
  std::string filepath = '/' + this->generateVoteFilename(RANDOM_FILENAME_LEN);

  // Create a new file with an unique name
  while (!this->createFile(filepath)) {
    filepath = '/' + this->generateVoteFilename(RANDOM_FILENAME_LEN);
  }

  // Send the vote to the server until the content in the server matches the expected value
  std::string readVote;
  while (this->readFile(filepath, readVote)) {
    if (readVote.compare(voteContent) != 0) {
      this->writeFile(filepath, voteContent);
    }
  }
  
  return true;
}
