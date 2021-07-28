#include <iostream>
#include <fstream>
#include <string>
#include "Logger.hpp"

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

