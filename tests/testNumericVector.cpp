#include <iostream>

#include "../numericVector.h"

int main(int argc, char** argv)
{
	NumericVectorHyperparameters nvh;

	NumericVector<int> nv0(nvh);
	nv0.getParameters("42 1.1 2.1 3.1 4.1");
	std::cout << nv0.getDesc() << "\n";

	NumericVector<double> nv1(nvh);
	nv1.getParameters("42 1.1 2.1 3.1 4.1");
	std::cout << nv1.getDesc() << "\n";
}
