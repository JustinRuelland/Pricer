#pragma once
#include <iostream>
#include <string>
#include "asset.h"
using namespace std;

class option {
protected : 
	double K = 0 ; // strike
	double T = 0; // maturity (in years)
	asset empty_asset;
	asset* ptr_underlying = &empty_asset;

	static double r; // risk free rate

public :
	// Constructor
	option() {};
	option(option&);
	option(asset* ptr_underlying, double K, double T);

	//// Member functions
	virtual double price() const = 0;
	virtual string type() const = 0;
	virtual void replication() const = 0;
	
	// Getter
	double get_K() const { return this->K; } ;
	double get_T() const { return this->T; };
	asset* get_ptr_underlying() const { return this->ptr_underlying; } ;
	asset* get_allias_underlying() { return this->ptr_underlying; }; 

	// Setter
	void set_K(double K) { this->K = K; };
	void set_T(double T) { this->T = T; };
	void set_ptr_underlying(asset* ptr_underlying) { this->ptr_underlying = ptr_underlying; };

	static void set_r(double r) { option::r = r; };
	static double get_r() { return option::r; };

	// Non-member function
	friend ostream& operator<<(ostream& output, const option& o);
	friend istream& operator>>(istream& input, option& o);
};