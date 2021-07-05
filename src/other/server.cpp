#include "serverPadron.hpp"

#include <iostream>

int main(int argc, char const *argv[]) {
  serverPadron server;
  server.listenForever("8081");
  return 0;
}
