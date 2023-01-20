#include <iostream>
#include "european_call.h"
#include "european_put.h"
#include "cdf.h"
#include <string>

using namespace std;
#include "asset.h"

// Destructor
european_call::~european_call() {};

// Member function
double european_call::price() const {
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 1)) {
		int n = DividendCounter(T, (*ptr_underlying).get_alias_Dividends().get_Next(), (*ptr_underlying).get_alias_Dividends().get_Periods());
		double S_hat = S*pow(1- (*ptr_underlying).get_alias_Dividends().get_Rate(),n);
		
		european_call call_for_computation(K, S_hat, T, sigma);

		return call_for_computation.price();
	}
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 2)) {
		double rate = (*ptr_underlying).get_alias_Dividends().get_Rate();
		double K_for_computation = K * exp(rate * T);

		european_call call_for_computation(K_for_computation, S, T, sigma);

		return exp(-rate * T) * call_for_computation.price();
	}
	else{
		double d_1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
		double d_2 = d_1 - sigma * sqrt(T);

		double V = S * cdf(d_1) - K * exp(-r * T) * cdf(d_2);

		return V;
	}
};

string european_call::type() const {
	string name = "European call";
	return name;
};

void european_call::replication() const {
	european_put put(K, S, T, sigma);

	cout << "The replication of the buy of this " << this->type() << ", which value is "<<this->price()<<", is : ";
	cout << "\n * The buy on the same underlying asset of an " << put <<put.price();
	cout << "\n * The buy of the underlying asset." << put.get_S();
	cout << "\n * The borrow of " << exp(-r * T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << put.price() + S - exp(-r * T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}