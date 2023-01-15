#pragma once
class option {
protected : 
	double K = 1 ; // strike
	double S = 1; // spot price
	double T = 1; // maturity (in years)
	double sigma = 1; // volatility

	static double r; // risk free rate

public :
	virtual double price() const = 0;
	
};