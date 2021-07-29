#ifndef FSSERVER_HPP
#define FSSERVER_HPP

#include <string>
#include <vector>

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"

// NETWORK
#include "Network/Socket.hpp"

// SERVERS
#include "Server.hpp"

#define CREATE_OPCODE 'a'
#define WRITE_OPCODE  'b'
#define READ_OPCODE   'c'
#define DELETE_OPCODE 'd'
#define EXIST_OPCODE  'e'
#define PRINT_HD_CODE 'p'

class FSServer : public Server {
 protected:
  FileSystem* fileSystem = nullptr;

 public:
  FSServer() = delete;
  FSServer(FileSystem& fs);
  FSServer(const FileSystem& other) = delete;
  FSServer(FileSystem&& other) = delete;
  ~FSServer();

 protected:
  bool fileExists(std::string& filepath);
  bool createFile(std::string& filepath);
  bool writeFile(std::string& filepath, std::vector<char>& content);
  bool deleteFile(std::string& filepath);
  bool readFile(std::string& filepath, std::string& output);

 protected:
  size_t parseWriteOp(std::string datagram);

 protected:
  bool handleFileSystemOps(std::string datagram, Socket& socketWithClient);
  virtual void handleClientConnection(Socket& socketWithClient);
};

#endif
