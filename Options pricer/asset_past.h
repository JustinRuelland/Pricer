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
	int DividendsPeriods; // The period between two dividend's payments for an asset with lump payment of dividends
	int Init_NextDividend;
	int Curr_NextDividend;

	int Current_time;

	public :

	asset(); 
	asset(double SpotPrice, double Volatility, int DividendsType, double DividendsRate, int DividendsPeriods, int Init_NextDividend);
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

	int get_DividendsPeriods() const;
	// void set_DividendsPeriods(double Periodicity);

	int get_NextDividend() const;

	double get_DividendsPayoff(int current_time, double SpotPrice) const;

	void Asset_Actualization(int time, double SpotPrice);

	void Test1();

};
