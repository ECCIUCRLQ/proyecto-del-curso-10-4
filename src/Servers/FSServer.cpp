#include "FSServer.hpp"

#include <iostream>

FSServer::FSServer(FileSystem& fs) : fileSystem(&fs) {
  std::cout << "Server: listening..." << std::endl;
}

FSServer::~FSServer() {}

void FSServer::handleClientConnection(Socket& socketWithClient) {
  // Read the data from the socket
  std::string readLine;
  std::string filepath;
  std::vector<char> data;
  size_t filepathLen = 0;

  // Read until null char
  if (socketWithClient.readLine(readLine, 0)) {
    if (readLine.length() > 1) {
      char opCode = readLine.at(0);
      switch (opCode) {
        // Create File
        case CREATE_OPCODE:
          filepath = readLine.substr(1);
          this->createFile(socketWithClient, filepath);
          break;
        // Write File
        case WRITE_OPCODE:
          filepathLen = this->parseWriteOp(readLine.substr(1));
          // If filepath len > 0
          if (filepathLen) {
            filepath = readLine.substr(1, filepathLen);
            data.resize(readLine.length() - filepathLen - 2);
            readLine.copy(data.data(), data.size(), filepathLen + 2);
            this->writeFile(socketWithClient, filepath, data);
          } else {
            this->sendErrorMessage(socketWithClient);
          }
          break;
        // Read File
        case READ_OPCODE:
          filepath = readLine.substr(1);
          this->readFile(socketWithClient, filepath);
          break;
        // Delete File
        case DELETE_OPCODE:
          filepath = readLine.substr(1);
          this->deleteFile(socketWithClient, filepath);
          break;
        case EXIST_OPCODE:
          filepath = readLine.substr(1);
          this->fileExists(socketWithClient, filepath);
          break;
        case 'p':
          this->fileSystem->printHD();
          break;
        default:
          this->sendErrorMessage(socketWithClient, 'a');
          break;
        }
    } else {
      // Send a generic error message
      this->sendErrorMessage(socketWithClient);
    }
  } else {
    // Send a generic error message
    this->sendErrorMessage(socketWithClient);
  }

  std::cout << "Server: listening..." << std::endl;
}

void FSServer::sendErrorMessage(Socket& socket, char errCode) {
  std::cout << "Server: sending error code: " << (int)errCode << std::endl;
  socket << '0';

  if (errCode) {
    socket << errCode;
  }

  socket.send();
  socket.close();
}

size_t FSServer::parseWriteOp(std::string datagram) {
  size_t ret = 0;

  while (datagram.at(ret) != '\n' && ret < datagram.length()) {
    ++ret;
  }

  // If there is no data or \n
  if (ret + 2 >= datagram.length()) {
    ret = 0;
  }

  return ret;
}

void FSServer::fileExists(Socket& socket, std::string& filepath) {
  if (this->fileSystem->search(filepath)) {
    std::cout << "Exists: " << filepath << " was found" << std::endl;
    socket << "1";
    socket.send(); 
  } else {
    std::cout << "Exist: " << filepath << " was not found" << std::endl;
    this->sendErrorMessage(socket);
  }
}

void FSServer::createFile(Socket& socket, std::string& filepath) {
  if (this->fileSystem->createFile(filepath, 0, 0, ALLOW_ALL)) {
    std::cout << "\tCreate: created file " << filepath << std::endl;
    socket << "1";
    socket.send();
  } else {
    std::cout << "\tCreate: could not create file" << std::endl;
    this->sendErrorMessage(socket);
  }
}

void FSServer::writeFile(Socket& socket, std::string& filepath, std::vector<char>& content) {
  std::cout << "Write: writing on file " << filepath;
  content.resize(content.size());
  std::cout << std::endl << '\t' << content.data() << std::endl;

  if (this->fileSystem->writeFile(filepath, content.data(), content.size(), 0, 0)) {
    socket << "1";
    socket.send();
  } else {
    this->sendErrorMessage(socket);
  }
}

void FSServer::readFile(Socket& socket, std::string& filepath) {
  std::cout << "Read: reading file " << filepath << std::endl;

  size_t fileSize = this->fileSystem->sizeOfFile(filepath, 0, 0);
  if (fileSize > 0) {
    std::vector<char> data(fileSize);
    if (this->fileSystem->readFile(filepath, data.data(), fileSize, 0, 0)) {
      socket << "1";
      std::string readData(data.data(), data.size());
      socket << readData;
      socket.send();
    } else {
      std::cout << "Error a" << std::endl;
      this->sendErrorMessage(socket);
    }
  } else {
    std::cout << "Error b" << std::endl;
    this->sendErrorMessage(socket);
  }
}

void FSServer::deleteFile(Socket& socket, std::string& filepath) {
  std::cout << "Delete: deleting file " << filepath << std::endl;
  this->sendErrorMessage(socket);
  // TODO(any): implement this after testing deleteFile in FileSystem
}
