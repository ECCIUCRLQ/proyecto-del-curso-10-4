#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std ;

int main(){
	//char datos[256]; 
	//string str;
	unsigned int MAX_BUF_LENGTH = 256;
	char buffer[MAX_BUF_LENGTH];
	int socketServidor = 0, conexion = 0, n =0, clientServidor = 0;

	struct sockaddr_in ip;
	socketServidor = socket(AF_INET, SOCK_STREAM, 0);

	memset(&ip, '0', sizeof(ip));
	//memset(datos, '0', sizeof(datos));
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = htonl(INADDR_ANY);
	ip.sin_port = htons(1337);
	
  bind(socketServidor, (struct sockaddr*)&ip , sizeof(ip));
	listen(socketServidor , 20);
 
  int msjs =0 ;sleep(1);
  struct sockaddr_storage ipRemoto;
  socklen_t l= sizeof(ipRemoto);
  char strIpRemoto[INET6_ADDRSTRLEN];
  int port;
  cout << endl << "[SERVIDOR ESCUCHANDO]" << endl ;
	while(msjs<5000){
		conexion= accept(socketServidor, (struct sockaddr*) &ipRemoto, &l);
    if (conexion!=-1) {
      cout << "[MENSAJE RECIBIDO] #"<< ++msjs ;
      struct sockaddr_in *s = (struct sockaddr_in *)&ipRemoto;
      port = ntohs(s->sin_port);
      inet_ntop(AF_INET, &s->sin_addr, strIpRemoto, sizeof strIpRemoto);
      cout << " IP Remoto: " << strIpRemoto << endl ;
      int bytenum = 256;
      size_t filesize = 0, buffersize = 0;
      FILE * file = NULL;

      // cambiar nombbre a variable para poder modificar
      file = fopen("dos.PNG","wb");
      buffersize = 256;
      while(bytenum != 0) {
      	bytenum = recv(conexion, buffer, buffersize, 0);

      	fwrite(buffer,sizeof(char),bytenum, file);
      }
      fclose(file);
      close(conexion);
           
      close(socketServidor);
    }
    //sleep(1);
  }

  cout << endl << "[SERVIDOR DETENIDO]" << endl;
  return 0;
}