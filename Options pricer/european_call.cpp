#include <iostream>
#include "european_call.h"
#include "european_put.h"
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

void european_call::replication() const {
	european_put put(this->K, this->S, this->T, this->sigma);

	cout << "The replication of the buy of this " << this->type() << ", which value is "<<this->price()<<", is : ";
	cout << "\n * The buy on the same underlying asset of an " << put;
	cout << "\n * The buy of the underlying asset.";
	cout << "\n * The borrow of " << exp(-r * this->T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << put.price() + this->S - exp(-r * this->T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}