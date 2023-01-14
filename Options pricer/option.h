#pragma once
class option {
protected : 
	double T = 1; // maturity
	double K = 1; // strike
	double S = 1; // spot price
	double sigma = 1; // volatility

	static double r; // risk free rate

public :
	virtual void price() = 0;
};