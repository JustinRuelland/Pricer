#include <iostream>
#include "european_call.h"
#include "european_put.h"
#include "cdf.h"
#include <string>
#include "asset.h"
using namespace std;


// Destructor
european_call::~european_call() {};

// Member function
double european_call::price() const {
	double S = (*ptr_underlying).get_SpotPrice();
	double sigma = (*ptr_underlying).get_Volatility();

	// lump dividends
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 1)) {
		int n = DividendCounter(T, (*ptr_underlying).get_alias_Dividends().get_Next(), (*ptr_underlying).get_alias_Dividends().get_Periods());
		double S_hat = S*pow(1- (*ptr_underlying).get_alias_Dividends().get_Rate(),n);
		
		/* we need to commpue the price of an option,
		with the strike the same strike and the same maturity,
		on an underlying with the spot price S_hat and the same volatility, but WITH NO DIVIDENDS*/

		asset asset_for_computation; //asset without dividend
		asset_for_computation.set_SpotPrice(S_hat);
		asset_for_computation.set_Volatility(sigma);
		asset* ptr_underlying_for_computation = &asset_for_computation;

		european_call call_for_computation(ptr_underlying_for_computation, K, T);

		return call_for_computation.price();
	}
	// continuous dividends
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 2)) {
		double rate = (*ptr_underlying).get_alias_Dividends().get_Rate();
		double K_for_computation = K * exp(rate * T);

		/* we need to commpute the price of an option, 
		with the strike "K_for_computation" and same maturity, 
		on an underlying with the same spot price and volatility, but WITH NO DIVIDENDS*/

		asset asset_for_computation; //asset without dividend
		asset_for_computation.set_SpotPrice(S);
		asset_for_computation.set_Volatility(sigma);
		asset* ptr_underlying_for_computation = &asset_for_computation;

		european_call call_for_computation(ptr_underlying_for_computation,K_for_computation,T);

		return exp(-rate * T) * call_for_computation.price();
	}
	// no dividend
	else{
		double d_1 = (log(S / K) + (r + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
		double d_2 = d_1 - sigma * sqrt(T);

		double V = S * cdf(d_1) - K * exp(-r * T) * cdf(d_2);

		return V;
	}
};

string european_call::type() const {
	string name = "european call";
	return name;
};

void european_call::replication() const {
	double S = (*ptr_underlying).get_SpotPrice();

	european_put put(ptr_underlying, K, T);

	cout << "The replication of the buy of this " << this->type() << ", which value is "<<this->price()<<", is : ";
	cout << "\n * The buy on the same underlying asset of an " << put;
	cout << "\n	* The buy of the underlying asset.";
	cout << "\n * The borrow of " << exp(-r * T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << put.price() + S - exp(-r * T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}