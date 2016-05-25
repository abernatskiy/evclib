#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include "environmentByNumber.h"

//#define ENVIRONMENT_FIELDS 0
#define ENVIRONMENT_FIELDS 1
#include "situatedController.h"

#ifndef FIELD_SEPARATOR
#define FIELD_SEPARATOR ' '
#endif // FIELD_SEPARATOR

class TestController
{
public:
	std::string contrStr;

	int ID;
	double eval;

	TestController(std::string genotype) :
		eval(-1.0)
	{
		std::stringstream ss(genotype);
		std::string idStr;
		std::getline(ss, idStr, FIELD_SEPARATOR);
		std::getline(ss, contrStr);
		if(idStr.empty() || contrStr.empty())
		{
			std::cout << "Wrong genotype line for TestController: " << genotype << std::endl;
			exit(EXIT_FAILURE);
		}
		ID = std::stoi(idStr);
	};

	std::string getDesc()
	{
		std::ostringstream ss;
		ss << ID << FIELD_SEPARATOR << contrStr;
		return ss.str();
	};
};

typedef SituatedController<EnvironmentByNumber,TestController> SitCont;

void printSitContInfo(SitCont* sc)
{
	std::cout << "Description: " << sc->getDesc() << std::endl
						<< "Description of the Environment: " << sc->env->getDesc() << std::endl
						<< "Number of environment: " << sc->env->envNum << std::endl
						<< "Description of the Controller: " << sc->contr->getDesc() << std::endl;
}

int main(int argc, char** argv)
{
	// // Testing the test controller
	// TestController tst0("123 0 1 2 3");
	// std::cout << tst0.getDesc() << std::endl;
	// TestController tst1("123");
	// TestController tst2("");

	SitCont sctst0("123 0 1 2 3");
	printSitContInfo(&sctst0);

	SitCont sctst1(sctst0);
	printSitContInfo(&sctst1);
	return 0;
}
