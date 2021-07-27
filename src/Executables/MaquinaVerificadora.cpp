#include <string>

#include "GUI/MaquinaVerificadora.hpp"

int main(int argc, char *argv[]) {
  if (argc >= 3) {
    std::string ip = argv[1];
    std::string port = argv[2];

    MaquinaVerificadora mv(ip, port);
    mv.run();
  }
  return 0;
}
