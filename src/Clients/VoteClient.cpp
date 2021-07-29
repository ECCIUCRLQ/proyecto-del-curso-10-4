#include "VoteClient.hpp"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

VoteClient::VoteClient(FileSystem& fs, const std::string& parentIp,
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

VoteClient::~VoteClient() {
}

bool VoteClient::getClassAndID() {
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
  std::string filepath = this->generateVoteFilename(RANDOM_FILENAME_LEN);

  // Create a new file with an unique name
  while (!this->createFile(filepath)) {
    filepath = this->generateVoteFilename(RANDOM_FILENAME_LEN);
  }
  std::cout << "1" << std::endl;

  // Send the vote to the server until the content in the server matches the expected value
  std::string readVote = "";
  while (!this->readFile(filepath, readVote)) {
    if (readVote.compare(voteContent) != 0) {
      this->writeFile(filepath, voteContent);
    }
  }

  // Tell the server to distribute the vote once its correct
  this->distributeVote(filepath);
  
  return true;
}

bool VoteClient::distributeVote(const std::string& filepath) {
  bool ret = false;

  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = DIST_VOTE_OPCODE + filepath;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
  if (response.length() > 0 && response.at(0) == '1') {
    ret = true;
  }

  socket.close();
  return ret;
}

bool VoteClient::sendVoteToClient(const std::string& filepath, const std::string& voteContent) {
  if (!this->fileExists(filepath)) {
    std::cout << "Trying to create file" << std::endl;
    this->createFileLocal(filepath);
  }

  // Send the vote to the server until the content in the server matches the expected value
  std::string readVote = "";
  while (!this->readFile(filepath, readVote)) {
    if (readVote.compare(voteContent) != 0) {
      this->writeFileLocal(filepath, voteContent);
    }
  }

  return true;
}

bool VoteClient::createFileLocal(const std::string& filepath) {
  bool ret = true;

  if (!this->fileExists(filepath)) {
    TcpClient client;
    Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

    std::string datagram = CREATE_OPCODE + filepath;
    this->sendDatagram(socket, datagram);

    std::string response = this->readSocketResponse(socket);
    if (response.length() == 0 && response.at(0) != '1') {
      ret = false;
    }

    socket.close();
  }

  return ret;
}

bool VoteClient::writeFileLocal(const std::string& filepath, const std::string& content) {
  bool ret = false;

  if (this->fileExists(filepath)) {
    TcpClient client;
    Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

    std::string datagram = WRITE_OPCODE + filepath + '\n' + content;
    this->sendDatagram(socket, datagram);

    std::string response = this->readSocketResponse(socket);
    if (response.length() > 0 && response.at(0) == '1') {
      ret = true;
    }

    socket.close();
  }

  return ret;
}
