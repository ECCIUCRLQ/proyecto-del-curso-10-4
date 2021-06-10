#ifndef PADRON_HPP
#define PADRON_HPP

#include <map>
#include <string_view>
#include <string>

class Padron {
 private:
	struct datoVotante{
    std::string nombre;
	  int codigo;
	  int voto;
  };
	std::map<std::string,datoVotante> mapaPadron;
	
 public:
  Padron();
  ~Padron();
    void agregarVotante(std::string carnet);
	void setNombre(std::string carnet,std::string nombre);
	void setCodigo(std::string carnet,int codigo);
	void setVoto(std::string carnet,int voto);
	std::string getNombre(std::string carnet);
	int getCodigo(std::string carnet);
	int getVoto(std::string carnet);
	std::string getCarnet(int codigo);
};


#endif
