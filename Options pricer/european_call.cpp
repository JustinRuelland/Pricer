#include <iostream>
#include "european_call.h"
#include "cdf.h"

// Constructors
european_call::european_call() {
	this->K = 1;
	this->S = 1;
	this->T = 1;
	this->sigma = 1;
}

european_call::european_call(double& K, double& S, double& T, double& sigma) {
	this->K = K;
	this->S = S;
	this->T = T;
	this->sigma = sigma;
}

european_call::european_call(european_call& call) {
	this->K = call.K;
	this->S = call.S;
	this->T = call.T;
	this->sigma = call.sigma;
}

// Destructor
european_call::~european_call() {};

// Member function
double european_call::price() const {
	double d_1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	double d_2 = d_1 - sigma * sqrt(T);

	double V = S * cdf(d_1) - K * exp(-r * T) * cdf(d_2);

	return V;
}

std::ostream &operator<<(std::ostream &output, const european_call & call) {

	output << "\nMaturity : " << call.T <<" ans\n"<<"Spot price : "<< call.S << "\nStrike : "<< call.K << "\nVolatility : "<<call.sigma<<"\nRisk free rate : "<<option::get_r()<<"\n";

	return output;
}