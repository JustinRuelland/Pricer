#include <iostream>
#include "european_call.h"
#include "cdf.h"

double european_call::price() const{
	double d_1 = (log(S / K) + (r + pow(sigma, 2) / 2)*T) / (sigma * sqrt(T));
	double d_2 = d_1 - sigma * sqrt(T);

	double V = S * cdf(d_1) - K * exp(-r * T) * cdf(d_2);

	return V;
}

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
