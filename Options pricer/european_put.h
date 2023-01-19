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

	// Destructor
	~european_put();

	// Member function
	double price() const;
	string type() const;
	void replication() const;
};