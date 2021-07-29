#include <iostream>
#include <string>

// FILE SYSTEM
#include "FileSystem/FileSystem.hpp"
#include "FileSystem/HardDrive.hpp"

// SERVERS
#include "Servers/PadronServer.hpp"

// VOTACION
#include "Votacion/PadronManager.hpp"

int main(int argc, char const *argv[]) {
  // Validate the amount of arguments
  if (argc < 3) {
    return EXIT_FAILURE;
  }

  // Get the filepath for the CSV containing the data
  std::string filepath = argv[1];

  // Get the port to be used
  std::string port = argv[2];

  // File System for the PadronManager
  HardDrive hd(1024 * 20);
  FileSystem fs(1024 * 20, &hd);

  // Instance of the PadronManager
  PadronManager padronManager(filepath, fs);

  // Create and start the server
  PadronServer server(padronManager);
  server.listenForever(port.c_str());

  return EXIT_SUCCESS;
}
