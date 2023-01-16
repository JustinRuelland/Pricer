#pragma once

class asset {
	
	protected :

	double SpotPrice;
	double Volatility;

	int DividendsType; 
	/*  An asset without dividends =0; 
		An asset with lump payment of dividends =1; 
		An asset with continuous dividend payment =2; */

	double DividendsRate;
	double DividendsPeriods; // The period between two dividend's payments for an asset with lump payment of dividends
	double NextDividend;

	public :

	asset(); 
	asset(double SpotPrice, double Volatility, int DividendsType, double DividendsRate, double DividendsPeriods, double NextDividend);
	asset(const asset& A1);
	~asset();

	double get_SpotPrice() const;
	// void set_SpotPrice(double S);

	double get_Volatility() const;
	// void set_Volatility(double V);

	int get_DividendsType() const;
	// void set_dividendsType(int T);

	double get_DividendsRate() const;
	// void set_DividendsRate(double r);

	double get_DividendsPeriods() const;
	// void set_DividendsPeriods(double Periodicity);

	double get_NextDividend() const;

	double get_DividendsPayoff(double current_time) const;





};
