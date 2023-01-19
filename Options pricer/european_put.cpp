#include <iostream>
#include "european_put.h"
#include "european_call.h"
#include <string>
using namespace std;

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

string european_put::type() const {
	string name = "European put";
	return name;
}

void european_put::replication() const {
	european_call call(this->K, this->S, this->T, this->sigma);

	cout << "The replication of the buy of this " << this->type() << ", which value is " << this->price() << ", is : ";
	cout << "\n * The buy on the same underlying asset of an " << call;
	cout << "\n * The sell of the underlying asset.";
	cout << "\n * The investment of " << exp(-r * this->T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << call.price() - this->S + exp(-r * this->T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}

