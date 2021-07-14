#include "FSClient.hpp"

FSClient::FSClient(FileSystem& fs, const std::string& serverIp,
  const std::string& serverPort) : Client(), fs(&fs) {
  this->serverIp = serverIp;
  this->serverPort = serverPort;
}

FSClient::~FSClient() {
}

bool FSClient::fileExists(const std::string& filepath) {
  bool ret = false;

  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = EXIST_OPCODE + filepath;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
  if (response.length() > 0 && response.at(0) == '1') {
    ret = true;
  }

  socket.close();
  return ret;
}

bool FSClient::createFile(const std::string& filepath) {
  bool ret = false;

  if (!this->fileExists(filepath) && this->createLocalFile(filepath)) {
    TcpClient client;
    Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

    std::string datagram = CREATE_OPCODE + filepath;
    this->sendDatagram(socket, datagram);

    std::string response = this->readSocketResponse(socket);
    if (response.length() > 0 && response.at(0) == '1') {
      ret = true;
    }

    socket.close();
  }

  return ret;
}

bool FSClient::writeFile(const std::string& filepath, const std::string& content) {
  bool ret = false;

  if (this->fileExists(filepath)) {
    if (this->fs->search(filepath) != nullptr) {
      this->writeLocalFile(filepath, content);
    }

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

bool FSClient::readFile(const std::string& filepath, std::string& output) {
  bool ret = false;

  if (this->fileExists(filepath)) {
    TcpClient client;
    Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());
    
    std::string datagram = READ_OPCODE + filepath;
    this->sendDatagram(socket, datagram);

    std::string response = this->readSocketResponse(socket);
    if (response.length() > 0 && response.at(0) == '1') {
      response = response.substr(1);
      output = response;
      ret = true;
    }

    socket.close();
  }

  return ret;
}

bool FSClient::deleteFile(const std::string& filepath) {
  bool ret = false;

  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = DELETE_OPCODE + filepath;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
  if (response.length() > 0 && response.at(0) == '1') {
    ret = true;
  }

  socket.close();
  return ret;
}

bool FSClient::printDisk() {
  bool ret = false;

  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = std::string(1, PRINT_HD_CODE);
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
  if (response.length() > 0 && response.at(0) == '1') {
    ret = true;
  }

  socket.close();
  return ret;
}

bool FSClient::createLocalFile(const std::string& filepath) {
  return this->fs->createFile(filepath, 0, 0, ALLOW_ALL);
}

bool FSClient::writeLocalFile(const std::string& filepath, const std::string& data) {
  return this->fs->writeFile(filepath, data.c_str(), data.length(), 0, 0);
}

std::string FSClient::readLocalFile(const std::string& filepath) {
  std::string ret = "";
  
  if (this->fs->search(filepath)) {
    size_t sizeOfFile = this->fs->sizeOfFile(filepath, 0, 0);
    if (sizeOfFile > 0) {
      std::vector<char> data(sizeOfFile);
      this->fs->readFile(filepath, data.data(), sizeOfFile, 0, 0);
      ret.assign(data.data(), sizeOfFile);
    }
  }

  return ret;
}
