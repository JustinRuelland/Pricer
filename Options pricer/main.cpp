#include <iostream>
#include "cdf.h"
#include "european_call.h"
#include "european_put.h"
#include "asian_call.h"
#include "asian_put.h"
#include "asset.h"
#include "gap_call.h"
#include "gap_put.h"

int main()
{
	std::cout << "Hello World!fef\n";

	double K = 60.0;
	double S = 60.0;
	double T = 1;
	double sigma = 0.1 ;
	//european_call call1(K, S, T, sigma);

	char name[20];
	
	asset Asset1;

	//// Naming of the asset
	std::cout << "Enter the name of your asset : ";
	std::cin >> name;
	Asset1.set_AssetName(name);
	Asset1.set_r(0.05);

	Asset1.set_SpotPrice(S);
	Asset1.set_Volatility(sigma);
	Asset1.set_CurrentTime(0.0);

	Asset1.get_alias_Dividends().set_Type(0);
	Asset1.get_alias_Dividends().set_Rate(0.0125);
	Asset1.get_alias_Dividends().set_Periods(0.25);
	Asset1.get_alias_Dividends().set_Next(0.1666);

	asset* ptr_asset1 =&Asset1;
	std::cout << Asset1 << std::endl;
	european_call mon_call;

	

	mon_call.replication();
	european_put mon_put(ptr_asset1, K, T);
	cout << mon_put.price() << endl;
	mon_put.replication();
	cout << (*ptr_asset1).get_r() << endl;

	asian_put mon_asiat(ptr_asset1, K, T);
	cout << mon_asiat.price() << endl;


	cout << mon_call << endl;


	// Illustrer la gestion d'un affichage d'une option créée par défaut
	european_put default_put;
	cout << default_put << endl;

	// Test gap
	gap_call mon_gap(ptr_asset1,K, T, K);
	cout << mon_gap.price() << endl;

	
	return 0;
}