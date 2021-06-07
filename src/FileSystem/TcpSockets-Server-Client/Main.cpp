#include "Padron.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  Padron padron;
   padron.agregarVotante("B95549");   
   padron.setCodigo("B95549",3894);
   padron.setNombre("B95549","Oscar Navarro");
   padron.setVoto("B95549",1);
   std::cout << padron.getNombre("B95549") << std::endl;
   std::cout << padron.getCodigo("B95549") << std::endl;
   std::cout << padron.getVoto("B95549") << std::endl;
  return 0;
}