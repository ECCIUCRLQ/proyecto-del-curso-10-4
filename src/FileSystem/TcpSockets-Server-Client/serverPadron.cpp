#include "serverPadron.hpp"
#include <cstring>
#include "Socket.hpp"
serverPadron::serverPadron(){
	this->padron = "pruebaB95549";
}

serverPadron::~serverPadron() {

}

void serverPadron::handleClientConnection(Socket& client) {
	std::string hilera = "";
	client.readLine(hilera);
	if(hilera.at(0) == 'a'){
		client << "Op code a"; 
		client.send();
	}
	else{
		if (hilera.at(0) == 'b'){
			//Aqui se le agrega al padron la nueva informacion recivida por el cliente
			client << "Op code = b"; 
			client.send();
		}
		else{
			client << "Op code = c";
		}
	}
 
}