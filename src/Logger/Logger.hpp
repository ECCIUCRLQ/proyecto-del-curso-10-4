#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#include <iostream>
#include <string>
class Logger {


	public:
	 void log(std::string method, std::string information, int success);



}; 

#endif  // LOGGER_H