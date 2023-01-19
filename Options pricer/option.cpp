#include "option.h"
#include <iostream>
using namespace std;

double option::r = 0.05;

// Constructors
option::option(double K, double S, double T, double sigma) {
	this->K = K;
	this->S = S;
	this->T = T;
	this->sigma = sigma;
};
option::option(option& o) {
	this->K = o.K;
	this->S = o.S;
	this->T = o.T;
	this->sigma = o.sigma;
};

// Overloading of the operators << and >> of iostream
std::ostream& operator<<(std::ostream& output, const option& o) {
	output << "an " << o.type() <<" with : " << "\n - Strike : " << o.K << "\n - Spot price : " << o.S << "\n - Maturity : " << o.T << " years" << "\n - Volatility : " << o.sigma << "\n - Risk free rate : " << option::get_r() * 100 << "%" << "\n - Price (Black-Scholes method) : " << o.price()<<"\n";
	return output;
};

std::istream& operator>>(std::istream& input, option& o) {
	cout << "\n\nYou are defining an " << o.type()<<".";
	cout <<"\n - Enter the option's strike : ";
	input >> o.K;
	cout << " - Enter the underlying asset's spot price : ";
	input >> o.S;
	cout << " - Enter the option's maturity : ";
	input >> o.T;
	cout << " - Enter the underlying's volatility : ";
	input >> o.sigma;

	cout << "The price of the " << o.type() << " you have just defined is : " << o.price() << ".\n";

	return input;
};