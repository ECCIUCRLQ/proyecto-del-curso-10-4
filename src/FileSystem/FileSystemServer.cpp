#include "FileSystemServer.hpp"



FileSystemServer::FileSystemServer(FileSystem* fs) {
  // Creates the Bitmap for free/used space in storage
this->fs = fs;

}

FileSystemServer::~FileSystemServer() {
  
}


bool FileSystemServer::receiveFile(std::string filepath, int user, int group){
    bool success = false;
	 // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Error al crear socket" << std::endl;
        return -1;
    }
		int puerto = 54000;
    // Bind the ip address and port to a socket

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(puerto);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
 
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << host << " conectado con el puerto " << service << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " conectado con el puerto " << ntohs(client.sin_port) << std::endl;
    }
 
    // Close listening socket
    close(listening);
 
    // While loop: accept and echo message back to client
    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error al recibir datos" << std::endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            success = true;
            std::cout << "Cliente desconectado " << std::endl;
            break;
        }
 
        std::cout << std::string(buf, 0, bytesReceived) << std::endl;
 
        // Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
	 // Close the socket
    close(clientSocket);

return success;
}
	

