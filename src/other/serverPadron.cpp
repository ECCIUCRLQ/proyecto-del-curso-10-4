#include "serverPadron.hpp"

#include <cstring>

serverPadron::serverPadron() {
}

serverPadron::~serverPadron() {
}

void serverPadron::handleClientConnection(Socket& client) {
	std::string hilera = "";
	client.readLine(hilera);
	std::cout << "Comando recivido: "<< hilera << std::endl;
	if(hilera.at(0) == 'a'){
		std::string carnet = "";
		for(int i = 1; i<hilera.length();++i){
			carnet+= hilera.at(i);
		}
		padron.agregarVotante(carnet);
		padron.setCodigo(carnet,12345);
		hilera = "Actualizado codigo en padron para carnet:";
		hilera += carnet;
		client << hilera; 
		client.send();
	}
	else{
		if (hilera.at(0) == 'b'){
			std::string codigo = "";
			int nCodigo = 0;
			for(int i = 1; i<hilera.length();++i){
			codigo+= hilera.at(i);
			}
			nCodigo = std::stoi(codigo);
			//Aqui se le agrega al padron la nueva informacion recivida por el cliente
			hilera = "Carnet asociado a codigo";
			hilera += codigo + ": " + padron.getCarnet(nCodigo); ;
			client << hilera;
			client.send();
		}
		else{
		std::string carnet = "";
		for(int i = 1; i<hilera.length();++i){
			carnet+= hilera.at(i);
		}
	
		padron.setVoto(carnet,1);
		hilera = "Actualizado voto en padron para carnet:";
		hilera += carnet;
		client << hilera; 
		client.send();
		}
	}
 
}