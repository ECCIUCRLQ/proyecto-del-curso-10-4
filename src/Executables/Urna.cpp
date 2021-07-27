#include <string>

#include "GUI/Urna.hpp"

int main(int argc, char *argv[]) {
  if (argc >= 3) {
    std::string ip = argv[1];
    std::string port = argv[2];

    Urna urna(ip, port);
    urna.run(argc, argv);
  }
  return 0;
}
