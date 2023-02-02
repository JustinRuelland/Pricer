#pragma once
#include "tools.h"
#include "option.h"

class american_put : public option {
public :
	// Constructors
	american_put() {};
	american_put(american_put& call) :option(call) {};
	american_put(asset* ptr_underlying, double K, double T) : option(ptr_underlying, K, T) {};

	// Destructor
	~american_put() ;

	// Member function
	double price() const;
	string type() const;
};