#include <iostream>
#include <cstdlib>

#include "parseCLI.h"

std::pair<std::string, std::string> parsecli::twoFilenamesForIO(int argc, char** argv, std::string appName)
{
	if(argc == 3)
		return std::make_pair(std::string(argv[1]), std::string(argv[2]));

	std::cout << "Usage: " << appName << " <pathToInputFile> <pathToOutputFile>\n";
	exit(EXIT_FAILURE);
}
