#include <iostream>
#include <sstream>
#include <fstream>
#define NOMBRE_ARCHIVO "ProductosExportados_SPOS3.csv"
using namespace std;

int main()
{
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ',';// esto se debe cambiar segun el delimitador que presenta el padron
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    // Leemos todas las líneas
    while (getline(archivo, linea))
    {

        stringstream stream(linea); // Convertir la cadena a un stream
        string idProducto, codigoBarras, descripcion, precioCompra, precioVenta, existencia, stock;
        // Extraer todos los valores de esa fila- todos estos valores se cambian segun los datos que se necesitan para el padron
        //getline(stream, idProducto, delimitador);
        //getline(stream, codigoBarras, delimitador);
        //getline(stream, descripcion, delimitador);
        //getline(stream, precioCompra, delimitador);
        //getline(stream, precioVenta, delimitador);
        //getline(stream, existencia, delimitador);
        //getline(stream, stock, delimitador);
        // Imprimir
        cout << "==================" << endl;
    // no es necesario imprimir los valores sino guardarlos 
    }

    archivo.close();
} 


