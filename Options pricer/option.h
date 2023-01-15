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

	double get_K() {return this->K;};
	double get_S() { return this->S; };
	double get_T() { return this->T; };
	double get_sigma() { return this->sigma; };

	void set_K(double& K) { this->K = K; };
	void set_S(double& S) { this->S = S; };
	void set_T(double& T) { this->T = T; };
	void set_sigma(double& sigma) { this->sigma = sigma; };
};