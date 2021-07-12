#include "PadronServer.hpp"
#include "HardDrive.hpp"
#include "FileSystem.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  PadronServer server(fs, "FACU_INGE");

  // Add clients
  server.addClient("172.24.131.223", "8082");#cambio para conexion entre maquinas
  server.addClient("127.0.0.1", "8083");

  server.listenForever("8081");

  return 0;
}
