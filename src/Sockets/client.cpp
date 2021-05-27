//libreria de entrada y salida de datos 
#include <iostream>
//#include <netdb.h>
//libreria para el uso de strings 
#include <string.h>
// libreria para las funciones de linux(read,write,close,etc)
#include <unistd.h>
//libreria para usarel inet
#include <arpa/inet.h>
 
using namespace std ;

int main(){
    int resultado=0 ;
    int s = 0,n = 0;
    char datos[256];
    //crea el socket
    struct sockaddr_in ipServidor;
    // llena el vector de datos con 0s
    memset(datos, '0' ,sizeof(datos));
    datos[15]='1';
    // hay que cambiar el tipo de socket, esta como un stream socket, hay que cambiarlo a un datagram socket 
    // el tercer parametro es el protocolo, cuando se pone 0 se pone un protocolo por default
    if((s = socket(AF_INET, SOCK_DGRAM, 0))< 0){
      cout << "Error de creación de socket" << endl;
      resultado=1 ;
    } else {//estos datos hay que cambiarlos para hacer un socket que soporte archivos
      ipServidor.sin_family = AF_INET;
      ipServidor.sin_port = htons(1337);
      //aqui se usa el inet
      ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
 	// se verifica la conexion
      //if(connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor))<0)
      if(sendto(s,datos,256,0,(struct sockaddr *)&ipServidor,sizeof(ipServidor))<0)
      {
        cout << endl << "Error de conexión por IP o puerto" << endl ;
        resultado= 2;
      } else {
       // aqui se usa unistd
       
        //while((n = read(s, datos, sizeof(datos))) > 0){
          //datos[n] = 0;
          //cout << endl << string(datos) << endl ;
        //}
 
        //if( n < 0){
        //  cout << endl << "Error de lectura" << endl ;
        //}
      }
    }
  
    return resultado;
}

