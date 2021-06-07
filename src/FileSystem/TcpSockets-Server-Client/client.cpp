#include "TcpClient.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  TcpClient client;
  Socket& socket = client.connect("127.0.0.1", "8081");
  std::string comando;
  comando = "cB95549";
  socket << comando;
  socket.send();
  std::string hileraRecibida;
  socket.readLine(hileraRecibida);
  std::cout << "Se recibio de servidor: " << hileraRecibida << std::endl;


  socket.close();

  return 0;
}
