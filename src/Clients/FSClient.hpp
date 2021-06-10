#ifndef FSCLIENT_HPP
#define FSCLIENT_HPP

#include <iostream>
#include <string>
#include <vector>

#include "FileSystem.hpp"
#include "HardDrive.hpp"
#include "Socket.hpp"
#include "TcpClient.hpp"

#define CREATE_OPCODE 'a'
#define WRITE_OPCODE  'b'
#define READ_OPCODE   'c'
#define DELETE_OPCODE 'd'
#define EXIST_OPCODE  'e'

#define CREATE_COMMAND  "create"
#define WRITE_COMMAND   "write"
#define READ_COMMAND    "read"
#define DELETE_COMMAND  "delete"
#define SEARCH_COMMAND  "search"

class FSClient {
 private:
  FileSystem* fs = nullptr;

 private:
  std::string serverIp = "127.0.0.1";
  std::string serverPort = "8081";

 public:
  FSClient(FileSystem& fs);
  ~FSClient();

 public:
  void shell();

 private:
  void parse(const std::string& input);

 public:
  bool fileExists(const std::string& filepath);
  bool createFile(const std::string& filepath);
  bool writeFile(const std::string& filepath, const std::string& data);
  bool readFile(const std::string& filepath);
  void deleteFile(const std::string& filepath);

 private:
  bool createLocalFile(const std::string& filepath);
  bool writeLocalFile(const std::string& filepath, const std::string& data);
  std::string readLocalFile(const std::string& filepath);
  bool deleteLocalFile(const std::string& filepath);

 private:
  void sendDatagram(Socket& socket, const std::string& datagram);
  std::string readSocketResponse(Socket& socket);
};

#endif
