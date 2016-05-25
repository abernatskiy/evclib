#ifndef GTOP_PARSE_CLI_H
#define GTOP_PARSE_CLI_H

#include <string>
#include <tuple>

namespace parsecli
{
	std::pair<std::string, std::string> twoFilenamesForIO(int argc, char** argv, std::string appName = "client");
}

#endif // GTOP_PARSE_CLI_H
