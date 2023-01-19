#pragma once
#include "option.h"

class asian_call : public option {
public:
	// Constructors
	asian_call() {};
	asian_call(double K, double S, double T, double sigma) :option(K, S, T, sigma) {};
	asian_call(asian_call& call) :option(call) {};

	// Destructor
	~asian_call();

	// Member function
	double price() const;
	string type() const;
};