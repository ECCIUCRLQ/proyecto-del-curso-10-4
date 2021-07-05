#include <iostream>
#include <thread>

#include "HardDrive.hpp"
#include "FileSystem.hpp"
#include "PadronServer.hpp"
#include "VoteShell.hpp"

void initServer(FileSystem* fs) {
  
}

int main(int argc, char const *argv[]) {
  HardDrive hd(1024 * 8);
  FileSystem fs(1024 * 8, &hd);
  PadronClient vc(fs, "127.0.0.1", "8081");

  std::cout << vc.updateVote("B94536") << std::endl;

  return 0;
}
