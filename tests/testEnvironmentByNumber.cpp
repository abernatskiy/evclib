#include <iostream>

#include "../environmentByNumber.h"

int main(int argc, char** argv)
{
	EnvironmentByNumber e0("11");
	std::cout << e0.getDesc() << std::endl;
	EnvironmentByNumber e1("12 5");
	std::cout << e1.getDesc() << std::endl;
//	EnvironmentByNumber e2("");
	EnvironmentByNumber e2("13 5 6");
	return 0;
}
