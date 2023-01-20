#include <iostream>
#include "cdf.h"
#include "european_call.h"
#include "european_put.h"
#include "asian_call.h"
#include "asian_put.h"
#include "asset.h"

int main()
{
	std::cout << "Hello World!\n";

	double K = 40.0;
	double S = 40.0;
	double T =0.5;
	double sigma = 0.30;
	european_call call1(K, S, T, sigma);

	european_call call2(call1);

	std::cout << call1.price() << std::endl;


	char name[20];
	
	asset Asset1;

	//// Naming of the asset
	// std::cout << "Enter the name of your asset : ";
	// std::cin >> name;
	// Asset1.set_AssetName(name);
	option::set_r(0.09);

	Asset1.set_SpotPrice(S);
	Asset1.set_Volatility(sigma);
	Asset1.set_CurrentTime(0.0);

	Asset1.get_alias_Dividends().set_Type(2);
	Asset1.get_alias_Dividends().set_Rate(0.0125);
	Asset1.get_alias_Dividends().set_Periods(0.25);
	Asset1.get_alias_Dividends().set_Next(0.1666);

	asset* ptr_asset1 =&Asset1;
	european_call mon_call(ptr_asset1, K, T);

	std::cout << Asset1 << std::endl;


	//Asset1.get_alias_Dividends().set_Rate(0.0);
	std::cout << mon_call.price() << std::endl;

	//mon_call.replication(); //-> problèmes

	asset Asset2(Asset1);

	Asset2.get_alias_Dividends().set_Type(0);

	asset* ptr_asset2 = &Asset2;
	european_call mon_call2(ptr_asset2, K, T);
	std::cout << mon_call2.price() << std:: endl;

	return 0;
}