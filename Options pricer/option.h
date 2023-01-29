#pragma once
#include <iostream>
#include <string>
#include "asset.h"
using namespace std;

class option {
protected : 
	double K = 0 ; // strike
	double T = 0; // maturity (in years)
	asset* ptr_underlying = nullptr;

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



	// Non-member function
	friend ostream& operator<<(ostream& output, const option& o);
	friend istream& operator>>(istream& input, option& o);
};