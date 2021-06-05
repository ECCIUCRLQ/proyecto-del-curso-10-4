#ifndef FILE_SYSTEM_SERVER_HPP
#define FILE_SYSTEM_SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "FileSystem.hpp"
#include <string>
#include <string.h>
class FileSystemServer {
	

  /**
   * @brief FileSystem of the node
   */
    FileSystem* fs;
 
 
   
  public:
  FileSystemServer(FileSystem*);
  ~FileSystemServer();



  bool receiveFile(std::string filepath, int user, int group);
 

};
#endif
