#include <iostream>
#include "european_put.h"
#include "european_call.h"
#include <string>
using namespace std;

// Destructor
european_put::~european_put() {};

// Member function
double european_put::price() const {
	double S = (*ptr_underlying).get_SpotPrice();
	double sigma = (*ptr_underlying).get_Volatility();

	// -------------- Lump dividends --------------
	if (((*ptr_underlying).get_alias_Dividends().get_Type() == 1)) {
		european_call equivalent_call(ptr_underlying, K, T);
		int n = DividendCounter(T, (*ptr_underlying).get_alias_Dividends().get_Next(), (*ptr_underlying).get_alias_Dividends().get_Periods()); // calculates the number of coupon detachments before the option's maturity
		double S_hat = S * pow(1 - (*ptr_underlying).get_alias_Dividends().get_Rate(), n); // S_hat = S * (1-dividente_rate)^n

		return equivalent_call.price() + exp(-r * T) * K - S_hat; // call-put parity for european with underlying with lump payments of dividends
	}
	// -------------- Continuous dividends and no dividend -------------
	else {
		european_call equivalent_call(this->ptr_underlying, K, T);
		double rate = (*ptr_underlying).get_alias_Dividends().get_Rate();
		double S_hat = S * exp(- rate * T);

		return equivalent_call.price() - S_hat + exp(-r * T) * K ; //We notice that if the rate is null, then we have the classical call-put parity. //equivalent_call.price()
	}
}

string european_put::type() const {
	string name = "european put";
	return name;
}

void european_put::replication() const {
	european_call call(ptr_underlying, K, T);

	cout << "The replication of the buy of this " << this->type() << ", which value is " << this->price() << ", is : ";
	cout << "\n * The buy on the same underlying asset of an " << call;
	cout << "\n * The sell of the underlying asset.";
	cout << "\n * The investment of " << exp(-r * T) * K << " on the risk free rate market. ";
	cout << "\n The balance of the replication is " << call.price() - (*ptr_underlying).get_SpotPrice() + exp(-r * T) * K << " (which is indeed equal to the spot price of the replicated option).\n\n\n";
}

