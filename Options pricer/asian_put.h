#pragma once
#include "option.h"


class asian_put : public option {
public:
	// Constructors
	asian_put();
	asian_put(double K, double S, double T, double sigma) :option(K, S, T, sigma) {};
	asian_put(asian_put& put) :option(put) {};
	asian_put(asset* ptr_underlying, double K, double T) : option(ptr_underlying, K, T) {};

	// Destructor
	~asian_put();

	// Member function
	double price() const;
	string type() const;
	void replication() const;
};