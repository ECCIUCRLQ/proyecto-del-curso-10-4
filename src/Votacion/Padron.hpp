#ifndef PADRON_HPP
#define PADRON_HPP

#include <map>
#include <string_view>
#include <string>
class Padron {
 private:
	struct datoVotante{
    	std::string nombre;
	std::string codigo;
	int voto;
   	std::string centroLoc;
	
  };
	std::map<std::string,datoVotante> mapaPadron;
	
 public:
  Padron();
  ~Padron();
    void agregarVotante(std::string carnet);
	void setNombre(std::string carnet,std::string nombre);
	void setCodigo(std::string carnet,std::string codigo);
	void setVoto(std::string carnet,int voto);
	void setCentroLoc(std::string carnet, std::string centroLoc);
	std::string getNombre(std::string carnet);
	std::string getCodigo(std::string carnet);
	int getVoto(std::string carnet);
	std::string getCentroLoc(std::string carnet);
	std::string getCarnet(std::string codigo);
};


#endif
