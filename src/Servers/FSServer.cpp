#include "FSServer.hpp"

#include <iostream>

FSServer::FSServer(FileSystem& fs) : fileSystem(&fs) {
  std::cout << "Server: listening..." << std::endl;
}

FSServer::~FSServer() {}

void FSServer::handleClientConnection(Socket& socketWithClient) {
  std::cout << "Server: listening..." << std::endl;
  std::string datagram = this->readLineFromSocket(socketWithClient);
  if (!this->handleFileSystemOps(datagram, socketWithClient)) {
    std::cout << "Error: opcode not supported" << std::endl;
    this->sendErrorMessage(socketWithClient);
  }
}

bool FSServer::handleFileSystemOps(std::string datagram, Socket& socketWithClient) {
  std::string filepath;
  char opCode;

  if (datagram.length() > 0) {
    opCode = datagram.at(0);

    // File Exist
    if (opCode == EXIST_OPCODE) {
      filepath = datagram.substr(1);
      if (this->fileExists(filepath)) {
        std::cout << "Exists: " << filepath << " was found" << std::endl;
        this->sendSuccessCode(socketWithClient);
      } else {
        std::cout << "Exists: " << filepath << " was not found" << std::endl;
        this->sendErrorMessage(socketWithClient);
      }
      return true;
    }

    // Create File
    if (opCode == CREATE_OPCODE) {
      filepath = datagram.substr(1);
      if (this->createFile(filepath)) {
        std::cout << "Create: created file " << filepath << std::endl;
        this->sendSuccessCode(socketWithClient);
      } else {
        std::cout << "Create: could not create file " << filepath << std::endl;
        this->sendErrorMessage(socketWithClient);
      }
      return true;
    }

    // Read File
    if (opCode == READ_OPCODE) {
      filepath = datagram.substr(1);
      std::string content;
      if (this->readFile(filepath, content)) {
        std::cout << "Read: could read the file " << filepath << std::endl;
        socketWithClient << "1";
        socketWithClient << content;
        socketWithClient.send();
      } else {
        std::cout << "Read: could not read the file " << filepath << std::endl;
        this->sendErrorMessage(socketWithClient);
      }
      return true;
    }

    // Delete File
    if (opCode == DELETE_OPCODE) {
      filepath = datagram.substr(1);
      if (this->deleteFile(filepath)) {
        std::cout << "Delete: could delete the file " << filepath << std::endl;
        this->sendSuccessCode(socketWithClient);
      } else {
        std::cout << "Delete: could not read the file " << filepath << std::endl;
        this->sendErrorMessage(socketWithClient);
      }
      return true;
    }

    // Write File
    if (opCode == WRITE_OPCODE) {
      size_t filepathLen = this->parseWriteOp(datagram.substr(1));
      if (filepathLen > 0) {
        std::vector<char> data;
        filepath = datagram.substr(1, filepathLen);
        data.resize(datagram.length() - filepathLen - 2);
        datagram.copy(data.data(), data.size(), filepathLen + 2);
        if (this->writeFile(filepath, data)) {
          std::cout << "Write: could write the file " << filepath << std::endl;
          this->sendSuccessCode(socketWithClient);
        } else {
          std::cout << "Write: could not write the file " << filepath << std::endl;
          this->sendErrorMessage(socketWithClient);
        }
      }
      return true;
    }

    // PRINT HDD
    if (opCode == PRINT_HD_CODE) {
      std::cout << "PrintHD: printing the hard drive" << std::endl;
      this->fileSystem->printHD();
      this->sendSuccessCode(socketWithClient);
      return true;
    }
  }
  
  // Return false if no action was taken
  return false;
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

bool FSServer::fileExists(std::string& filepath) {
  return this->fileSystem->search(filepath);
}

bool FSServer::createFile(std::string& filepath) {
  return this->fileSystem->createFile(filepath, 0, 0, ALLOW_ALL);
}

bool FSServer::writeFile(std::string& filepath, std::vector<char>& content) {
  content.resize(content.size());
  return this->fileSystem->writeFile(filepath, content.data(), content.size(), 0, 0);
}

bool FSServer::readFile(std::string& filepath, std::string& output) {
  bool ret = false;

  size_t fileSize = this->fileSystem->sizeOfFile(filepath, 0, 0);
  if (fileSize > 0) {
    std::vector<char> data(fileSize);
    if (this->fileSystem->readFile(filepath, data.data(), fileSize, 0, 0)) {
      std::string readData(data.data(), data.size());
      output = readData;
      ret = true;
    }
  }

  return ret;
}

bool FSServer::deleteFile(std::string& filepath) {
  // TODO(any): implement this after testing deleteFile in FileSystem
  return false;
}
