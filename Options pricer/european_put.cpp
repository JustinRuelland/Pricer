#include <iostream>
#include "european_put.h"
#include "european_call.h"
#include <string>
using namespace std;

// Destructor
european_put::~european_put() {};

// Member function
double european_put::price() const {
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 1)) {
		european_call equivalent_call(this->ptr_underlying, K, T);
		int n = DividendCounter(this->T, (*ptr_underlying).get_alias_Dividends().get_Next(), (*ptr_underlying).get_alias_Dividends().get_Periods());
		double S_hat = this->S * pow(1 - (*ptr_underlying).get_alias_Dividends().get_Rate(), n);

		return equivalent_call.price() + exp(-r * T) * K - S_hat;
	}
	else {
		european_call equivalent_call(this->ptr_underlying, K, T);
		double rate = (*ptr_underlying).get_alias_Dividends().get_Rate();
		double S_hat = S * exp(- rate * T);

		return equivalent_call.price() + exp(-r * T) * K - S_hat; //We notice that if the rate is null, then we have the classical call-put parity.
	}
}

string european_put::type() const {
	string name = "European put";
	return name;
}

void european_put::replication() const {
	european_call call(this->K, this->S, this->T, this->sigma);

	cout << "The replication of the buy of this " << this->type() << ", which value is " << this->price() << ", is : ";
	cout << "\n * The buy on the same underlying asset of an " << call;
	cout << "\n * The sell of the underlying asset.";
	cout << "\n * The investment of " << exp(-r * this->T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << call.price() - this->S + exp(-r * this->T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}

