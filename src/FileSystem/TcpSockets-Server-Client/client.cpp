#include "Network/TcpClient.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  TcpClient client;
  Socket& socket = client.connect("127.0.0.1", "8081");
  socket << "Esto es un texto de prueba";
  socket.send();

  socket.close();

  return 0;
}
