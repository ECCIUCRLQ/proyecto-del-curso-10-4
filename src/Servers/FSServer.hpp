#ifndef FSSERVER_HPP
#define FSSERVER_HPP

#include <string>
#include <vector>

#include "FileSystem.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"

#define CREATE_OPCODE 'a'
#define WRITE_OPCODE  'b'
#define READ_OPCODE   'c'
#define DELETE_OPCODE 'd'
#define EXIST_OPCODE  'e'

class FSServer : public TcpServer {
 private:
  FileSystem* fileSystem = nullptr;

 public:
  FSServer() = delete;
  FSServer(FileSystem& fs);
  FSServer(const FileSystem& other) = delete;
  FSServer(FileSystem&& other) = delete;
  ~FSServer();

 private:
  void fileExists(Socket& socket, std::string& filepath);
  void createFile(Socket& socket, std::string& filepath);
  void writeFile(Socket& socket, std::string& filepath, std::vector<char>& content);
  void deleteFile(Socket& socket, std::string& filepath);
  void readFile(Socket& socket, std::string& filepath);

 private:
  size_t parseWriteOp(std::string datagram);

 private:
  void sendErrorMessage(Socket& socket, char errCode = 0);

 public:
  void handleClientConnection(Socket& socketWithClient);
};

#endif
