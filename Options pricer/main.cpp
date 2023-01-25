#include <iostream>
#include "cdf.h"
#include "european_call.h"
#include "european_put.h"
#include "asian_call.h"
#include "asian_put.h"
#include "asset.h"

int main()
{
	std::cout << "Hello World!fef\n";

	double K = 50.0;
	double S = 40.0;
	double T =2;
	double sigma = 0.30 ;
	//european_call call1(K, S, T, sigma);

	char name[20];
	
	asset Asset1;

	//// Naming of the asset
	// std::cout << "Enter the name of your asset : ";
	// std::cin >> name;
	// Asset1.set_AssetName(name);
	asset::set_r(0.09);

	Asset1.set_SpotPrice(S);
	Asset1.set_Volatility(sigma);
	Asset1.set_CurrentTime(0.0);

	Asset1.get_alias_Dividends().set_Type(1);
	Asset1.get_alias_Dividends().set_Rate(0.0125);
	Asset1.get_alias_Dividends().set_Periods(0.25);
	Asset1.get_alias_Dividends().set_Next(0.1666);

	asset* ptr_asset1 =&Asset1;
	european_call mon_call(ptr_asset1, K, T);

	std::cout << Asset1 << std::endl;

	mon_call.replication();
	european_put mon_put(ptr_asset1, K, T);
	cout << mon_put.price() << endl;
	mon_put.replication();
	cout << asset::get_r() << endl;
	
	return 0;
}