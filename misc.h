#ifndef MISC_H
#define MISC_H

#include <limits.h>
#include <string.h>

#include <iostream>
#include <cstdlib>

#define WIDTH_OF_FILE_NAME 300

int countSpaces(const char* str)
{
	int len = strlen(str);
	int counter = 0;
	for(int i=0; i<len; i++)
		if(str[i] == ' ')
			counter++;
	return counter;
}

template<class RealNumber> RealNumber unitize(RealNumber in)
{
	// constrain to [0.,1.]
	RealNumber result = in;
	result = result<0.f ? 0.f : result;
	result = result>1.f ? 1.f : result;
	return (RealNumber)result;
}

int ipow(int base, int exp)
{
	// integer power - strangely absent in std
	int result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

int binomialCoeff(int n, int r)
{
	// perhaps there is a better way to do this
	double ans = 1.0;
	for(int j = 1; j <= r; ++j){
		ans = ans*n/j;
		n--;
	}
	if(!std::isfinite(ans) || ans >= (double) INT_MAX)
	{
		std::cout << "Binomial coefficient c(" << n << "," << r << ") is too large, exiting\n";
		exit(EXIT_FAILURE);
	}
	return (int)ans;
}

#endif // MISC_H
