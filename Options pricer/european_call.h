#pragma once
#include "option.h"
#include <iostream>
using namespace std;

class european_call : public option {
public :
	// Constructors
	european_call();
	european_call(double& K, double& S, double& T, double& sigma);

	european_call(european_call&);

	// Destructor
	~european_call() ;

	// Member function
	double price() const;

	friend ostream& operator<<(ostream& output, const european_call& call);
};