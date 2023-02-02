#pragma once
#include "tools.h"
#include "option.h"

class american_call : public option {
public :
	// Constructors
	american_call() {};
	american_call(american_call& call) :option(call) {};
	american_call(asset* ptr_underlying, double K, double T) : option(ptr_underlying, K, T) {};

	// Destructor
	~american_call() ;

	// Member function
	double price() const;
	string type() const;
};