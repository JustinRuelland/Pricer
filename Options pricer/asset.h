#pragma once

int DividendCounter(int Delta, int Next, int Periods);
char* NameCopie(const char chaine[20]);

class dividend {
protected:
	int Type; 
	/*  An asset without dividends =0; 
		An asset with lump payment of dividends =1; 
		An asset with continuous dividend payment =2; */

	double Rate;

	int Periods; 
	// The period between two dividend's payments for an asset with lump payment of dividends

	int Next;

public:
	//************** Primary functions **************
	dividend();
	dividend(int DividendsType, double DividendsRate, int DividendsPeriods, int NextDividend);
	dividend(const dividend&);
	~dividend(){};


	//************** Basic functions **************
	//*** Getter ***
	int get_Type() const;
	double get_Rate() const;
	int get_Periods() const;
	int get_Next() const;


	//*** Setter ***
	void set_Type(int);
	void set_Rate(double);
	void set_Periods(int);
	void set_Next(int);

};


class asset {
protected:
	//Asset Name
	char* AssetName; //We limit the AssetName at 19 characters


	//************** Basic features **************
	int CurrentTime;

	double SpotPrice;

	double Volatility;


	//************** Dividends feature **************

	dividend Dividends;

public:
	//************** Primary functions **************
	asset();
	asset(char AssetName[20], int CurrentTime, double SpotPrice, double Volatility, dividend Dividends);
	asset(const asset&);
	~asset();


	//************** Basic functions **************
	//*** Getter ***
	char* get_AssetName() const;
	int get_CurrentTime() const;
	double get_SpotPrice() const;
	double get_Volatility() const;
	dividend get_Dividends() const;

	//*** Setter ***
	void set_AssetName(char Name[20]);
	void set_CurrentTime(int);
	void set_SpotPrice(double);
	void set_Volatility(double);
	void set_Dividends(dividend);


	//************** Advanced functions **************

	void Asset_Actualization(int NewTime, double SpotPrice);
	asset Asset_Estimation(int Time, double RiskFreeRate) const;  
};






