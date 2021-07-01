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
#define PRINT_HD_CODE 'p'

class FSServer : public TcpServer {
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
  void sendSuccessCode(Socket& socket);
  void sendErrorMessage(Socket& socket, char errCode = 0);

 protected:
  std::string readLineFromSocket(Socket& socketWithClient);
  bool handleFileSystemOps(std::string datagram, Socket& socketWithClient);

 protected:
  virtual void handleClientConnection(Socket& socketWithClient);
};

#endif
