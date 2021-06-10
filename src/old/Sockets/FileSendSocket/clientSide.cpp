#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
using namespace std ;

int main(){
    int resultado=0;
    int str_length;
    int s = 0,n = 0;
    char datos[256];
    string comando;
    struct sockaddr_in ipServidor;
    FILE* file = NULL;
    memset(datos, 's' ,sizeof(datos));
 
    if((s = socket(AF_INET, SOCK_STREAM, 0))< 0){
      cout << "Error de creación de socket" << endl;
      resultado=1 ;
    } else {
      ipServidor.sin_family = AF_INET;
      ipServidor.sin_port = htons(1337);
      ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
 
      if(connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor))<0){
        cout << endl << "Error de conexión por IP o puerto" << endl ;
        resultado= 2;
      } else {
        size_t filesize, nsize = 0;
        size_t filesize2;
        // crea el archivo (cambiar a variable para modificar nombre)
        file = fopen("dos.PNG","rb");
        // calcula tamanio de file
        //puntero a primero
        fseek(file, 0, SEEK_END);
        filesize = ftell(file);
        fseek(file,0,SEEK_SET);
        // send content
        while(nsize!=filesize) {
          // read file to buffer
          int posSize = fread(datos,1,256,file);
          nsize+=posSize;
          send(s,datos,posSize,0);
        }
        fclose(file);
        close(s);
       
        if( n < 0){
          cout << endl << "Error de lectura" << endl ;
        }
      }
    }
  
    return resultado;
}