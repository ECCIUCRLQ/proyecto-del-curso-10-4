#include "FileSystemClient.hpp"
FileSystemClient::FileSystemClient(FileSystem* file) {

	this->fs = file;

}
FileSystemClient::~FileSystemClient() {

}
std::string FileSystemClient::sendSocket() {
    std::string archRecivido  = "";
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return "listo1";
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    std::string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return "Listo";
    }

    //	While loop:
    char buf[4096];
    std::string userInput;


    
        //		Enter lines of text
        std::string solicitud = "Padron";

        //		Send to server
        int sendRes = send(sock, solicitud.c_str(), solicitud.size() + 1, 0);
        if (sendRes == -1)
        {
            std::cout << "Could not send to server! Whoops!\r\n";
            
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
            archRecivido = std::string(buf, bytesReceived);
        }


    //	Close the socket
    close(sock);

    return archRecivido;
}
