#pragma once
#include "option.h"

class european_call : public option {
public :
	// Constructors
	european_call() {};
	european_call(double& K, double& S, double& T, double& sigma) :option(K, S, T, sigma) {};
	european_call(european_call& call) :option(call) {};

	// Destructor
	~european_call() ;

	// Member function
	double price() const;

};