/* COPYRIGHT Equipo Tronaditas 2021 */
// Clase para creacion de la bitacora
#include <iostream>
#include <fstream>
#include <string>
#include "Logger.hpp"
	/*
	* datos de la funcion log
	* @param method-metodo que se esta verificando
	* @param information- informacion retornada por el metodo
	* @param success-booleano de verificacion
	*/
void Logger::log (std::string method, std::string information, int success) {
	std::ofstream logFile;
	logFile.open("Logger.txt",std::ios::app);
	if (success == 1){
		logFile << "Invocación válida de método "<< method <<": " << information << "\n\n";
	} else {
		logFile << "Invocación inválida de método"<< method << ": "<< information << "\n\n";
	}
	logFile.close();

}

