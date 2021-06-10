
#ifndef FileSystemClient_HPP
#define FileSystemClient_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "HardDrive.hpp"
#include "FileSystem.hpp"
class FileSystemClient {

private:
	

public:
	FileSystem* fs;
	FileSystemClient(FileSystem* file);
	~FileSystemClient();
	std::string sendSocket();
	
};


#endif