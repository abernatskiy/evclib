// FIXME: Won't work with the new interfaces

/* Phenotype class consisting of an Environment and a
   Controller. Compatible with EvalQueue template.

   Constructs from the line of the following format:

   ID envf1 .. envfN contr_desc

   where:

     ID is the ID of the phenotype.

     envf1 to envfN are text fields describing the
       environment in which the controller is to be
       evaluated. N, the number of text fields,
       is controlled by ENVIRONMENT_FIELDS define
       directive (default value is 0).

     contr_desc is the text data (possibly consisting of
       fields) describing the
       controller to be evaluated.

     ' ' is the field separator defined by the
       FIELD_SEPARATOR define directive.

   Controller and Environment must be
   Phenotype-compliant classes, see the template and
   comments at evalQueue.h starting at line 18.
   Additionally, they must support initialization
   with strings of EVS-compatible format:

     ID envf0 .. envfN for Environment
     ID contr_descr for Controller

   Additionally, Environment class must be able to
   process empty genotypes (with zero fields, N=0).
*/

#ifndef EVCLIB_SITUATED_CONTROLLER_H
#define EVCLIB_SITUATED_CONTROLLER_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>

#ifndef ENVIRONMENT_FIELDS
#define ENVIRONMENT_FIELDS 0
#endif // ENVIRONMENT_FIELDS

#ifndef FIELD_SEPARATOR
#define FIELD_SEPARATOR ' '
#endif // FIELD_SEPARATOR

template<class Environment,class Controller>
class SituatedController
{
public:
	Environment* env;
	Controller* contr;

	int ID;
	double eval;

	SituatedController(std::string);
	SituatedController(const SituatedController& other);
	~SituatedController();

	std::string getDesc();
};

// DEFINITIONS

template<class Environment,class Controller>
SituatedController<Environment,Controller>::SituatedController(std::string fullGenotype)
{
	// separate the full genotype into strings for ID, environment fields anf the rest of stuff
	std::stringstream ss(fullGenotype);

	std::string idStr;
	std::getline(ss, idStr, FIELD_SEPARATOR);

	std::vector<std::string> envFields;
	std::string field;
	for(int i=0; i<ENVIRONMENT_FIELDS; i++)
	{
		std::getline(ss, field, FIELD_SEPARATOR);
		envFields.push_back(field);
	}

	std::string contrDesc;
	std::getline(ss, contrDesc);

	// std::cout << "Parsed the fullGenotype into the following parts:" << std::endl
	// 					<< "ID: " << idStr << std::endl
	// 					<< "Environment fields:";
	// for(auto it: envFields)
	// 	std::cout << " " << it;
	// std::cout << std::endl
	// 					<< "Controller desc: " << contrDesc << std::endl;

	// reading the ID
	ID = std::stoi(idStr);

	// customarily assigning initial evaluation to -1.0
	eval = -1.0;

	// bringing Environment's genome together and contructing the instance
	std::ostringstream envGenSS;
	envGenSS << idStr;
	for(auto envField: envFields)
		envGenSS << " " << envField;
	env = new Environment(envGenSS.str());

	// same for Controller's instance
	std::ostringstream contrGenSS;
	contrGenSS << idStr << FIELD_SEPARATOR << contrDesc;
	contr = new Controller(contrGenSS.str());
}

template<class Environment,class Controller>
SituatedController<Environment,Controller>::SituatedController(const SituatedController& other) :
	ID(other.ID),
	eval(other.eval)
{
	env = new Environment(*other.env);
	contr = new Controller(*other.contr);
}

template<class Environment,class Controller>
SituatedController<Environment,Controller>::~SituatedController()
{
	delete env;
	delete contr;
}

template<class Environment,class Controller>
std::string SituatedController<Environment,Controller>::getDesc()
{
	std::string envID, envDesc, contrID, contrDesc;

	std::stringstream envStream(env->getDesc());
	std::getline(envStream, envID, FIELD_SEPARATOR);
	std::getline(envStream, envDesc);

	std::stringstream contrStream(contr->getDesc());
	std::getline(contrStream, contrID, FIELD_SEPARATOR);
	std::getline(contrStream, contrDesc);

	if(envID.compare(contrID) != 0)
	{
		std::cout << "IDs of Environment and Controller are different within the same SituatedController\n" <<
			"Most likely, this is due to some memory corruption. Exiting.\n";
		exit(EXIT_FAILURE);
	}

	std::ostringstream situatedControllerStream;
	situatedControllerStream << envID << FIELD_SEPARATOR << envDesc << FIELD_SEPARATOR << contrDesc;
	return situatedControllerStream.str();
}

#endif // EVCLIB_SITUATED_CONTROLLER_H
