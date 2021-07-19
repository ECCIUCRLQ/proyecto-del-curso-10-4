#include <iostream>
#include <string>

// CLIENTS
#include "Clients/PadronClient.hpp"

// FILE SYSTEM
#include "FileSystem/HardDrive.hpp"
#include "FileSystem/FileSystem.hpp"

// SHELLS
#include "Shells/PadronShell.hpp"


int main(int argc, char const *argv[]) {
  // Verify the amount of arguments
  if (argc < 3) {
    return EXIT_FAILURE;
  }

  // Server IP
  std::string serverIP = argv[1];

  // Server Port
  std::string serverPort = argv[2];

  // Instance of the PadronClient
  PadronClient client(serverIP, serverPort);

  // Shell
  PadronShell shell(client);
  shell.shell();

  return 0;
}
