#include <iostream>
#include "cdf.h"
#include "european_call.h"

int main()
{
	std::cout << "Hello World!\n";

	// Test pour prix d'un call
	double K = 50.0;
	double S = 52.0;
	double T = 0.25;
	double sigma = 0.30;
	european_call call1(K,S,T,sigma);
	std::cout << call1.price() << std::endl;
}