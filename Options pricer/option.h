#pragma once
#include <iostream>
using namespace std;

class option {
protected : 
	double K = 0 ; // strike
	double S = 0; // spot price
	double T = 0; // maturity (in years)
	double sigma = 0; // volatility

	static double r; // risk free rate

public :
	// Constructor
	option() {};
	option(double K, double S, double T, double sigma);
	option(option&);

	//// Member functions
	virtual double price() const = 0;
	
	// Getter
	double get_K() {return this->K;};
	double get_S() { return this->S; };
	double get_T() { return this->T; };
	double get_sigma() { return this->sigma; };

	// Setter
	void set_K(double K) { this->K = K; };
	void set_S(double S) { this->S = S; };
	void set_T(double T) { this->T = T; };
	void set_sigma(double sigma) { this->sigma = sigma; };

	static void set_r(double r) { option::r = r; };
	static double get_r() { return option::r; }

	// Non-member function
	friend ostream& operator<<(ostream& output, const option& o);
	friend istream& operator>>(istream& input, option& o);
};