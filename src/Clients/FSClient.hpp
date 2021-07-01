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
 protected:
  FileSystem* fs = nullptr;

 protected:
  std::string serverIp = "";
  std::string serverPort = "";

 public:
  FSClient(FileSystem& fs, const std::string& serverIp, const std::string& serverPort);
  virtual ~FSClient();

 public:
  void shell();

 protected:
  void parse(const std::string& input);

 protected:
  virtual bool fileExists(const std::string& filepath);
  virtual bool createFile(const std::string& filepath);
  virtual bool writeFile(const std::string& filepath, const std::string& data);
  virtual bool readFile(const std::string& filepath, std::string& output);
  virtual bool deleteFile(const std::string& filepath);

 protected:
  void fileExistsShell(const std::string& filepath);
  void createFileShell(const std::string& filepath);
  void writeFileShell(const std::string& filepath, const std::string& data);
  void readFileShell(const std::string& filepath);
  void deleteFileShell(const std::string& filepath);

 protected:
  bool createLocalFile(const std::string& filepath);
  bool writeLocalFile(const std::string& filepath, const std::string& data);
  std::string readLocalFile(const std::string& filepath);
  bool deleteLocalFile(const std::string& filepath);

 protected:
  void sendDatagram(Socket& socket, const std::string& datagram);
  std::string readSocketResponse(Socket& socket);
};

#endif
