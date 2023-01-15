#pragma once
#include "option.h"

class european_call : public option {
public :
	european_call();
	european_call(double& K, double& S, double& T, double& sigma);

	double price() const;
};