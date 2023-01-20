#pragma once
#include "option.h"
#include <string>
using namespace std;

class european_call : public option {
public :
	// Constructors
	european_call() {};
	european_call(double K, double S, double T, double sigma) :option(K, S, T, sigma) {};
	european_call(european_call& call) :option(call) {};
	european_call(asset* ptr_underlying, double K, double T) : option(ptr_underlying, K, T) {};

	// Destructor
	~european_call() ;

	// Member function
	double price() const;
	string type() const;
	void replication() const;
};