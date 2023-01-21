#include "option.h"
#include <iostream>
#include "asset.h"
using namespace std;

double option::r = 0.05;

// Constructors
option::option(option& o) {
	this->K = o.K;
	this->T = o.T;
	this->ptr_underlying = o.ptr_underlying;
};

option::option(asset* ptr_underlying, double K, double T) {
	this->K = K;
	this->T = T;
	this->ptr_underlying = ptr_underlying;
}

// Overloading of the operators << and >> of iostream
std::ostream& operator<<(std::ostream& output, const option& o) {
	asset* ptr_underlying = o.get_ptr_underlying();
	double S = (*ptr_underlying).get_SpotPrice();
	double sigma = (*ptr_underlying).get_Volatility();

	output << "an " << o.type() <<" with : " << "\n	- Strike : " << o.K << "\n	- Spot price : " << S << "\n	- Maturity : " << o.T << " years" << "\n	- Volatility : " << sigma << "\n	- Risk free rate : " << option::get_r() * 100 << "%" << "\n	- Price (Black-Scholes method) : " << o.price()<<"\n";
	return output;
};

std::istream& operator>>(std::istream& input, option& o) {
	asset* ptr_underlying = o.get_ptr_underlying();
	double S = (*ptr_underlying).get_SpotPrice();
	double sigma = (*ptr_underlying).get_Volatility();

	cout << "\n\nYou are defining an " << o.type()<<".";
	cout <<"\n - Enter the option's strike : ";
	input >> o.K;
	cout << " - Enter the underlying asset's spot price : ";
	input >> S;
	cout << " - Enter the option's maturity : ";
	input >> o.T;
	cout << " - Enter the underlying's volatility : ";
	input >> sigma;

	cout << "The price of the " << o.type() << " you have just defined is : " << o.price() << ".\n";

	return input;
};