#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(){
  
  struct sockaddr_in cliente;
  struct hostent *servidor;
  servidor = gethostbyname(host); 
  if(servidor == NULL)
  { //Comprobación
    printf("Host erróneo\n");
    return 1;
  }
  int puerto, conexion;
  char buffer[100];
  conexion = socket(AF_INET, SOCK_STREAM, 0); 
  bzero((char *)&cliente, sizeof((char *)&cliente)); //La función bzero() es como memset() pero inicializando a 0 todas la variables
        
  cliente.sin_family = AF_INET; 
  cliente.sin_port = htons(puerto); 
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
 


  
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0){ 
    printf("Error conectando con el host\n");
    close(conexion);
    return 1;
  }
  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  
  
  //buffer es el mensaje a  enviar
  buffer = mensaje;
  send(conexion, buffer, 100, 0); //envio
  bzero(buffer, 100);
  recv(conexion, buffer, 100, 0); //recepción
  printf("%s", buffer);
  
  return 0;
}
