#include <iostream>
#include "european_put.h"
#include "european_call.h"

// Constructors
european_put::european_put() {
	this->K = 1;
	this->S = 1;
	this->T = 1;
	this->sigma = 1;
}

european_put::european_put(double& K, double& S, double& T, double& sigma) {
	this->K = K;
	this->S = S;
	this->T = T;
	this->sigma = sigma;
}

european_put::european_put(european_put& put) {
	this->K = put.K;
	this->S = put.S;
	this->T = put.T;
	this->sigma = put.sigma;
}

// Destructor
european_put::~european_put() {};

// Member function
double european_put::price() const {
	option* opt;

	return 0.0;
}
