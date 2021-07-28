/* COPYRIGHT Equipo Tronaditas 2021 */
// Clase para creacion de la bitacora
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#include <iostream>
#include <string>
class Logger {
	/*
	* datos de la funcion log
	* @param method-metodo que se esta verificando
	* @param information- informacion retornada por el metodo
	* @param success-booleano de verificacion
	*/

	public:
	 void log(std::string method, std::string information, int success);



}; 

#endif  // LOGGER_H
