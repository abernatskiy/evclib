#include <iostream>

#define QUEUE_VEROBOSE_EVALUATION

#include "evalQueue.h"

class testPhenotype
{
public:
	std::string penotype;
	int ID;
	double eval;

	testPhenotype(std::string s)
	{
		penotype = s + " phenotype";
	};

	std::string getDesc()
	{
		return "desc" + penotype;
	};
};

int main(int argc, char** argv)
{
	auto eq = EvalQueue<testPhenotype>("/tmp/indiv", "/tmp/evals");
	for(int i=0; i<20; i++)
	{
		std::cout << "Current queue:" << std::endl;
		eq.print();
		std::cout << std::endl << std::endl;

		auto phPtr = eq.getNextPhenotypePtr();
		phPtr->eval = (double) phPtr->penotype.size();
	}
	std::cout << "That's all" << std::cout;
	return 0;
}
