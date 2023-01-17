#include <iostream>
#include "european_put.h"
#include "european_call.h"

// Destructor
european_put::~european_put() {};

// Member function
double european_put::price() const {
	double K = this->K;
	double S = this->S;
	double T = this->T;
	double sigma = this->sigma;

	european_call equivalent_call(K, S, T, sigma);

	return equivalent_call.price() + exp(-r * T)*K-S;
}
