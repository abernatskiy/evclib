/* Compile with
	g++ -std=c++11 -o testDirect ../../ann/direct.cpp testDirect.cpp

	Correct output when used with logistic transfer function:

	ID=42

	1.0000 0.5000
	-0.5000 1.0000
	1.0000 1.0000
	1.0000 1.0000

	Input: {1,0,0,0,} Output: {0.731059,0.622459,}
	Input: {0,1,0,0,} Output: {0.377541,0.731059,}
	Input: {0,0,1,0,} Output: {0.731059,0.731059,}
	Input: {0,0,0,1,} Output: {0.731059,0.731059,}
	Input: {1,1,-1,1,} Output: {0.622459,0.817574,}

	Comparison values:
	 sigmoid(1.5) = 0.817574
	 sigmoid(1) = 0.731059
	 sigmoid(0.5) = 0.622459
	 sigmoid(-0.5) = 0.377541

*/

#include <iostream>
#include <vector>

#include "../../ann/direct.h"
#include "../../ann/transferFunctions.h"

ANNNodeState sigmoid(ANNNodeState x)
{
//	return x>1. ? 1. : (x<0. ? 0. : x); // piecewise-linear transfer
	return logistic<ANNNodeState>(x); // from transferFunctions.h
}

int main(int argc, char** argv)
{
	ANNDirectHyperparameters hyp;
	hyp.inputNodes = 4;
	hyp.outputNodes = 2;
	hyp.transferFunction = sigmoid;

	ANNDirect nn0(hyp);
	nn0.getParameters("42 1 0.5 -0.5 1 1 1 1 1");
	nn0.print();
	std::vector<Percept> testInputs{{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}, {1,1,-1,1}};
	for(auto testInput : testInputs)
	{
		auto testOutput = nn0.output(testInput);
		std::cout << "Input: " << str(testInput) << " Output: " << str(testOutput) << std::endl;
	}
	std::cout << std::endl;

	std::vector<ANNNodeState> compVals{1.5, 1.0, 0.5, -0.5};
	std::cout << "Comparison values: " << std::endl;
	for(auto val : compVals)
		std::cout << " sigmoid(" << val << ") = " << sigmoid(val) << std::endl;
	return 0;
}
