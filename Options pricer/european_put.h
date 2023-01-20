#pragma once
#include "option.h"
#include <string>
using namespace std;

class european_put : public option {
public:
	// Constructors
	european_put();
	european_put(double K, double S, double T, double sigma) :option(K, S, T, sigma) {};
	european_put(european_put& put) :option(put) {};
	european_put(asset* ptr_underlying, double K, double T) : option(ptr_underlying, K, T) {};

	// Destructor
	~european_put();

	// Member function
	double price() const;
	string type() const;
	void replication() const;
};