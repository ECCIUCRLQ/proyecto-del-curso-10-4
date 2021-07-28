#include <string>

#include "GUI/Urna.hpp"

int main(int argc, char *argv[]) {
  if (argc >= 6) {
    std::string padronIp = argv[1];
    std::string padronPort = argv[2];
    std::string voteIp = argv[3];
    std::string votePort = argv[4];
    std::string serverPort = argv[5];

    Urna urna(padronIp, padronPort, voteIp, votePort, serverPort);
    urna.run(argc, argv);
  }
  return 0;
}
