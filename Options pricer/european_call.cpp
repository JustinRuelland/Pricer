#include <iostream>
#include "european_call.h"
#include "cdf.h"
#include <string>
using namespace std;

// Destructor
european_call::~european_call() {};

// Member function
double european_call::price() const {
	double d_1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	double d_2 = d_1 - sigma * sqrt(T);

	double V = S * cdf(d_1) - K * exp(-r * T) * cdf(d_2);

	return V;
};

string european_call::type() const {
	string name = "European call";
	return name;
};