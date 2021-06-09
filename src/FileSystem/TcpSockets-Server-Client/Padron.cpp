#include "Padron.hpp"
#include <cstring>

Padron::Padron(){
	
}

Padron::~Padron() {

}

void Padron::agregarVotante(std::string carnet){
	mapaPadron[carnet].codigo = 0;
    mapaPadron[carnet].nombre = "";
    mapaPadron[carnet].voto = 0;
}

void Padron::setNombre(std::string carnet,std::string nombre){
	this->mapaPadron[carnet].nombre = nombre;
}

void Padron::setCodigo(std::string carnet,int codigo){
	this->mapaPadron[carnet].codigo = codigo;
}

void Padron::setVoto(std::string carnet,int voto){
	this->mapaPadron[carnet].voto = voto;
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

std::string Padron::getCarnet(int codigo){
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




