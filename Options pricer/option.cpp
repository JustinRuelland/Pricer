#include "option.h"
#include <iostream>
using namespace std;

double option::r = 0.05;

std::ostream& operator<<(std::ostream& output, const option& o) {
	output << "\nMaturity : " << o.T << " ans\n" << "Spot price : " << o.S << "\nStrike : " << o.K << "\nVolatility : " << o.sigma << "\nRisk free rate : " << option::get_r()*100 <<"%"<< "\n\nPrice (Black-Scholes method) : " << o.price();
	return output;
};

std::istream& operator>>(std::istream& input, option& o) {
	cout << "Enter the underlying asset's spot price : ";
	input >> o.S;
	cout << "Enter the underlying's volatility : ";
	input >> o.sigma;
	cout << "Enter the option's maturity : ";
	input >> o.T;
	cout << "Enter the option's strike :";
	input >> o.K;
		
	return input;
};