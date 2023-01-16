#include <iostream>
#include "asset.h"


double get_SpotPrice();
// void set_SpotPrice(double S);

double get_Volatility();
// void set_Volatility(double V);

int get_DividendsType();
// void set_dividendsType(int T);

double get_DividendsRate();
// void set_DividendsRate(double r);

double get_DividendsPeriods();
// void set_DividendsPeriods(double Periodicity);

double get_DividendsPayoff(double current_time);

double get_NextDividend();

asset::asset(){
	this->SpotPrice = 0;
	this->Volatility = 0;
	this->DividendsType = 0;
	this->DividendsRate = 0;
	this->DividendsPeriods = 0;
	this->NextDividend = 0;
}

asset::asset(double SpotPrice, double Volatility, int DividendsType, double DividendsRate, double DividendsPeriods, double NextDividend){
	this->SpotPrice = SpotPrice;
	this->Volatility = Volatility;
	this->DividendsType = DividendsType;
	this->DividendsRate = DividendsRate;
	this->DividendsPeriods = DividendsPeriods;
	this->NextDividend = NextDividend;
}

asset::asset(const asset& A1){
	this->SpotPrice = A1.SpotPrice;
	this->Volatility = A1.Volatility;
	this->DividendsType = A1.DividendsType;
	this->DividendsRate = A1.DividendsRate;
	this->DividendsPeriods = A1.DividendsPeriods;
	this->NextDividend = A1.NextDividend;
}

asset::~asset(){};

double asset::get_SpotPrice() const{
	return SpotPrice;
}

double asset::get_Volatility() const{
	return Volatility;
}

int asset::get_DividendsType() const{
	return DividendsType;
}

double asset::get_DividendsRate() const{
	return DividendsRate;
}

double asset::get_DividendsPeriods() const{
	return DividendsPeriods;
}

double asset::get_DividendsPayoff(double current_time) const{
	return NextDividend;
}
/*
double asset::get_DividendsPayoff(double current_time) const{
	if (DividendsType == 0){
		return 0;
	}else if (DividendsType == 1){
		if(current_time == NextDividend){

		}
	}
}
*/



int main(int argc, char const *argv[])
{
	std::cout << 9.2%3 << std::endl;
	return 0;
}