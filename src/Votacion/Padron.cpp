#include "Padron.hpp"
#include <cstring>

Padron::Padron(){
}

Padron::~Padron() {
}

void Padron::agregarVotante(std::string carnet){
  mapaPadron[carnet].codigo = "";
  mapaPadron[carnet].nombre = "";
  mapaPadron[carnet].voto = 0;
  mapaPadron[carnet].centroLoc = "";
}

void Padron::setNombre(std::string carnet,std::string nombre){
	this->mapaPadron[carnet].nombre = nombre;
}

void Padron::setCodigo(std::string carnet,std::string codigo){
	this->mapaPadron[carnet].codigo = codigo;
}

void Padron::setVoto(std::string carnet,int voto){
	this->mapaPadron[carnet].voto = voto;
}

void Padron::setCentroLoc(std::string carnet,std::string centroLoc){
	this->mapaPadron[carnet].centroLoc = centroLoc;
}

std::string Padron::getNombre(std::string carnet){
	return this->mapaPadron[carnet].nombre;
}

int Padron::getCodigo(std::string carnet){
	return this->mapaPadron[carnet].codigo;
}

int Padron::getVoto(std::string carnet){
	return this->mapaPadron[carnet].voto;
}

std::string Padron::getCentroLoc(std::string carnet){
	return this->mapaPadron[carnet].centroLoc;
}

std::string Padron::getCarnet(std::string codigo){
	std::string carnet;

	auto iter = mapaPadron.begin();
  while (iter != mapaPadron.end()) {
    if(iter->second.codigo == codigo){
		  carnet = iter->first;
	  }
    ++iter;
  }

  return carnet;
}
