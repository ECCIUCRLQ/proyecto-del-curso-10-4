#include "FSClient.hpp"

FSClient::FSClient(FileSystem& fs) : fs(&fs) {
}

FSClient::~FSClient() {
}

void FSClient::shell() {
  std::string line;
  std::cout << "[FileSystem Client]: ";
  while (std::getline(std::cin, line)) {
    this->parse(line);
    std::cout << "[FileSystem Client]: ";
  }
}

void FSClient::parse(const std::string& input) {
  std::string command;
  std::string filepath;

  // Search for the first space
  std::string::size_type pos = input.find(' ');

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

  // No opcode matches
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());
  socket << "p46421";
  socket.send();
  socket.close();
  this->fs->printHD();
  std::cout << "Error: invalid command" << std::endl;
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
      std::cout << filepath << " created successfully" << std::endl;
    } else {
      std::cout << "Could not create " << filepath << std::endl;
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
      std::cout << filepath << " written successfully" << std::endl;
      ret = true;
    } else {
      std::cout << "Could not write " << filepath << std::endl;
    }

    socket.close();
  }

  return ret;
}

bool FSClient::readFile(const std::string& filepath) {
  bool ret = false;

  if (this->fileExists(filepath)) {
    TcpClient client;
    Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());
    
    std::string datagram = READ_OPCODE + filepath;
    this->sendDatagram(socket, datagram);

    std::string response = this->readSocketResponse(socket);
    if (response.length() > 0 && response.at(0) == '1') {
      response = response.substr(1);
      std::cout << response << std::endl;
    } else {
      std::cout << "Could not read " << filepath << std::endl;
    }

    socket.close();
  }

  return ret;
}

void FSClient::deleteFile(const std::string& filepath) {
  TcpClient client;
  Socket& socket = client.connect(this->serverIp.c_str(), this->serverPort.c_str());

  std::string datagram = DELETE_OPCODE + filepath;
  this->sendDatagram(socket, datagram);

  std::string response = this->readSocketResponse(socket);
  if (response.length() > 0 && response.at(0) == '1') {
    std::cout << filepath << " deleted successfully" << std::endl;
  } else {
    std::cout << "Could not delete " << filepath << std::endl;
  }

  socket.close();
  return;
}

void FSClient::sendDatagram(Socket& socket, const std::string& datagram) {
  socket << datagram;
  socket.send();
}

std::string FSClient::readSocketResponse(Socket& socket) {
  std::string ret;
  socket.readLine(ret, 0);
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
