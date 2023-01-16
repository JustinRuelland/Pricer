#include "option.h"
#include <iostream>
using namespace std;

double option::r = 0.05;

std::ostream& operator<<(std::ostream& output, const option& call) {
	output << "\nMaturity : " << call.T << " ans\n" << "Spot price : " << call.S << "\nStrike : " << call.K << "\nVolatility : " << call.sigma << "\nRisk free rate : " << option::get_r() << "\n\nPrice (Black-Scholes method) : " << call.price();
	return output;
};