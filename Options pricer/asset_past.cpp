#include <iostream>
#include "asset.h"

/*
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

double asset::get_NextDividend() const{

void Asset_Actualization(double time, double SpotPrice);
*/

asset::asset(){
	this->SpotPrice = 0;
	this->Volatility = 0;
	this->DividendsType = 0;
	this->DividendsRate = 0;
	this->DividendsPeriods = 0;
	this->Init_NextDividend = 0;
	this->Curr_NextDividend = 0;
	this->Current_time=0
}

asset::asset(double SpotPrice, double Volatility, int DividendsType, double DividendsRate, int DividendsPeriods, int Init_NextDividend, int Current_time=0){
	this->SpotPrice = SpotPrice;
	this->Volatility = Volatility;
	this->DividendsType = DividendsType;
	this->DividendsRate = DividendsRate;
	this->DividendsPeriods = DividendsPeriods;
	this->Init_NextDividend = Init_NextDividend;
	this->Curr_NextDividend = Init_NextDividend;
	this->Current_time = Current_time;
}

asset::asset(const asset& A1){
	this->SpotPrice = A1.SpotPrice;
	this->Volatility = A1.Volatility;
	this->DividendsType = A1.DividendsType;
	this->DividendsRate = A1.DividendsRate;
	this->DividendsPeriods = A1.DividendsPeriods;
	this->Init_NextDividend = A1.Init_NextDividend;
	this->Curr_NextDividend = A1.Curr_NextDividend;
	this->Current_time = A1.Current_time;
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

int asset::get_DividendsPeriods() const{
	return DividendsPeriods;
}

int asset::get_NextDividend() const{
	return Curr_NextDividend;
}

void asset::Asset_Actualization(int time, double SpotPrice){
	this->SpotPrice = SpotPrice;
	this->Current_time = time;
	this->Curr_NextDividend = (this->DividendsPeriods - time%this->DividendsPeriods + this->Init_NextDividend)%this->DividendsPeriods;
}


double asset::get_DividendsPayoff(int current_time, double SpotPrice) const{
	if (DividendsType == 0){
		return 0;
	}else if (DividendsType == 1){
		asset A1 = *this;
		A1.Asset_Actualization()
		if(){
			return DividendsRate
		}
	}
}

/*
void asset::Test1(void){
	asset A1 = *this;
	A1.SpotPrice = 2;
	std::cout << "La fonction s execute" << A1.get_SpotPrice() << std::endl;
	return;
}
*/


int main(int argc, char const *argv[])
{
	asset A;
	std::cout << A.get_SpotPrice() << std::endl;
	A.Test1();
	std::cout << A.get_SpotPrice() << std::endl;
	return 0;
}









