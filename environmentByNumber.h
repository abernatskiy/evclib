// FIXME: Won't work with new interface

#ifndef EVCLIB_ENVIRONMENT_BY_NUMBER_H
#define EVCLIB_ENVIRONMENT_BY_NUMBER_H

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>

#ifndef FIELD_SEPARATOR
#define FIELD_SEPARATOR ' '
#endif // FIELD_SEPARATOR

class EnvironmentByNumber
{
public:
  int envNum;

	int ID;
	double eval;
	EnvironmentByNumber(std::string);
  std::string getDesc();
};

// DEFINITIONS

EnvironmentByNumber::EnvironmentByNumber(std::string genome) :
	envNum(-1), eval(-1.0)
{
	std::stringstream genomeStringStream(genome);

	std::string idStr, valStr, restStr;
	std::getline(genomeStringStream, idStr, FIELD_SEPARATOR);
	std::getline(genomeStringStream, valStr, FIELD_SEPARATOR);
	std::getline(genomeStringStream, restStr);

	if(idStr.empty() || !restStr.empty())
	{
		std::cout << "Wrong genotype for EnvironmentByNumber: it must contain an ID and a description of zero or one integers\n"
							<< "Genome in question: " << genome << std::endl;
		exit(EXIT_FAILURE);
	}

	ID = std::stoi(idStr);
	if(!valStr.empty())
		envNum = std::stoi(valStr);
}

std::string EnvironmentByNumber::getDesc()
{
	std::ostringstream ss;
	ss << ID;
	if(envNum!=-1)
	 ss << FIELD_SEPARATOR << envNum;
	return ss.str();
}

#endif // EVCLIB_ENVIRONMENT_BY_NUMBER_H
