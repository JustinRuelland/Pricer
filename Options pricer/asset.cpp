#include <iostream>
#include "asset.h"

asset(); 
asset(double SpotPrice, double Volatility, int DividendsType, double DividendsRate, double);
asset(const asset& A1);
~asset();

double get_SpotPrice() const;
// void set_SpotPrice(double S);

double get_Volatility() const;
// void set_Volatility(double V);

double get_DividendsType() const;
// void set_dividendsType(int T);

double get_DividendsRate() const;
// void set_DividendsRate(double r);

double get_DividendsPeriods() const;
// void set_DividendsPeriods(double Periodicity);

double get_DividendsPayoff(double time) const;

