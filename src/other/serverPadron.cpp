#include "serverPadron.hpp"
#include <cstring>
#include "../Network/Socket.hpp"
serverPadron::serverPadron(){
	ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ',';// esto se debe cambiar segun el delimitador que presenta el padron
    
    getline(archivo, linea);
	while (getline(archivo, linea))
    {

        stringstream stream(linea); // Convertir la cadena a un stream
        string carnet, nombre, apellido1, apellido2, yaVoto, codigo;
        // Extraer todos los valores de esa fila- todos estos valores se cambian segun los datos que se necesitan para el padron
        getline(stream, carnet, delimitador);
        getline(stream, nombre, delimitador);
        getline(stream, apellido1, delimitador);
		getline(stream, apellido2, delimitador);
		getline(stream, yaVoto, delimitador);
        getline(stream, codigo, delimitador);
        // Imprimir
        cout << "==================" << endl;
		padron.agregarVotante(carnet);
		nombre = nombre + apellido1 + apellido2;
		padron.setNombre(carnet,nombre);
		padron.setCodigo(carnet,stoi(codigo));
		padron.setVoto(carnet,stoi(yaVoto));
    // no es necesario imprimir los valores sino guardarlos 
    }

    archivo.close();

}	
serverPadron::~serverPadron() {

}

void serverPadron::handleClientConnection(Socket& client) {
	std::string hilera = "";
	client.readLine(hilera);
	std::cout << "Comando recibido: "<< hilera << std::endl;
	char opCode = hilera.at(0);

	if(opCode == 'a'){
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
		if (opCode == 'b'){
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

			if(opCode == 'c'){
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

				if(opCode == 'd'){
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
