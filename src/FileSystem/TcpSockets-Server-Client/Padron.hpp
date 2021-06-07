#ifndef PADRON_HPP
#define PADRON_HPP
#include <map>
class Padron {
	
	
	struct datoVotante{
       std::string nombre;
	   int codigo;
	   int voto;
     };
	std::map<std::string,datoVotante> mapaPadron;
	
  public:
  Padron();
  ~Padron();
	setNombre();
	setCodigo();
	setVoto();
	getNombre();
	getCodigo();
	getVoto();

 

};
#endif