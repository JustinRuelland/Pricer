#include <iostream>
#include "cdf.h"
#include "european_call.h"
#include "european_put.h"
#include "asian_call.h"
#include "asian_put.h"
#include "asset.h"
#include "gap_call.h"
#include "gap_put.h"
#include "european_lookback_call.h"
#include "european_lookback_put.h"

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
	european_call mon_call(ptr_asset1, K, T);
	
	

	mon_call.replication();
	european_put mon_put(ptr_asset1, K, T);
	cout << mon_put.price() << endl;
	mon_put.replication();
	cout << (*ptr_asset1).get_r() << endl;

	asian_put mon_asiat(ptr_asset1, K, T);
	cout << mon_asiat.price() << endl;


	cout << mon_call << endl;

	// Illustrer la gestion d'un affichage d'une option cr��e par d�faut
	european_put default_put;
	cout << default_put << endl;

	// Test gap
	gap_call mon_gap;
	cout << mon_gap.price() << endl;

	// Test lookback
	double m = 90;
	double M = 110;
	K = 50.0;
	S = 100.0;
	T = 1;
	sigma = 0.30;
	european_lookback_call mon_lookback_c(ptr_asset1, K, T, m);
	european_lookback_put mon_lookback_p(ptr_asset1, K, T, M);

	cout << "Risk Free Rate :" << endl;
	cout << (*ptr_asset1).get_r() << endl;
	cout << "Min spot:" << endl;
	cout << m << endl;
	cout << "Max spot:" << endl;
	cout << M << endl;
	std::cout << Asset1 << std::endl;
	cout << "Lookback Call Price:" << endl;
	cout << mon_lookback_c.price() << endl;
	cout << "Lookback Put Price:" << endl;
	cout << mon_lookback_p.price() << endl;

	
	return 0;
}