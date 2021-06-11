#include "serverPadron.hpp"
#include <cstring>
#include "Socket.hpp"
serverPadron::serverPadron(){
	//this->padron = padron;
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
		padron.setCodigo(carnet,rand()%600000 +1);
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

			if(hilera.at(0) == 'c'){
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
			else{

				if(hilera.at(0) == 'd'){
					std::string carnet = "";
					for(int i = 1; i<hilera.length();++i){
						carnet+= hilera.at(i);
					}
					hilera = "Votante con carnet: ";
					hilera += carnet + "  Voto: " + std::to_string(padron.getVoto(carnet));
					client << hilera; 
					client.send();

				}
				else{
					std::string carnet = "";
					for(int i = 1; i<hilera.length();++i){
						carnet+= hilera.at(i);
					}
					hilera = "Codigo asociado a carnet ";
					hilera += carnet + ": " + std::to_string(padron.getCodigo(carnet)); ;
					client << hilera;
					client.send();



				}
			}
		
		}
	}
 
}
