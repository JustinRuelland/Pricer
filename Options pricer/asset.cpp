#include <iostream>
#include "asset.h"

//************** Dividend functions **************

// Primary functions

dividend::dividend(){
	this->Type = 0;
	this->Rate = 0.0;
	this->Periods = 0;
	this->Next = 0;
}

dividend::dividend(int DividendsType, double DividendsRate, int DividendsPeriods, int NextDividend){
	this->Type = DividendsType;
	this->Rate = DividendsRate;
	this->Periods = DividendsPeriods;
	this->Next = NextDividend%DividendsPeriods;
}

dividend::dividend(const dividend& Div){
	this->Type = Div.Type;
	this->Rate = Div.Rate;
	this->Periods = Div.Periods;
	this->Next = Div.Next;
}


// Basic functions 

int dividend::get_Type() const{
	return Type;
}

double dividend::get_Rate() const{
	return Rate;
}

int dividend::get_Periods() const{
	return Periods;
}

int dividend::get_Next() const{
	return Next;
}

void dividend::set_Type(int Type){
	this->Type = Type;
}

void dividend::set_Rate(double Rate){
	this->Rate = Rate;
}

void dividend::set_Periods(int Periods){
	this->Periods = Periods;
}

void dividend::set_Next(int Next){
	this->Next = Next%this->Periods;
}


//************** Asset functions **************

// Primary functions

asset::asset(){
	dividend Div;

	this->CurrentTime = 0;
	this->SpotPrice = 0.0;
	this->Volatility = 0.0;
	this->Dividends = Div;
}

asset::asset(int CurrentTime, double SpotPrice, double Volatility, dividend Dividends){
	this->CurrentTime = CurrentTime;
	this->SpotPrice = SpotPrice;
	this->Volatility = Volatility;
	this->Dividends = Dividends;
}

asset::asset(asset& Asset1){
	this->CurrentTime = Asset1.CurrentTime;
	this->SpotPrice = Asset1.SpotPrice;
	this->Volatility = Asset1.Volatility;
	this->Dividends = Asset1.Dividends;
}


// Basic functions 

int asset::get_CurrentTime() const{
	return CurrentTime;
}

double asset::get_SpotPrice() const{
	return SpotPrice;
}

double asset::get_Volatility() const{
	return Volatility;
}

dividend asset::get_Dividends() const{
	return Dividends;
}

void asset::set_CurrentTime(int CurrentTime){
	this->CurrentTime = CurrentTime;
}

void asset::set_SpotPrice(double SpotPrice){
	this->SpotPrice = SpotPrice;
}

void asset::set_Volatility(double Volatility){
	this->Volatility = Volatility;
}

void asset::set_Dividends(dividend Dividends){
	this->Dividends = Dividends;
}


//Advanced functions

void asset::Asset_Actualization(int NewTime, double SpotPrice){
	int OldTime = this->CurrentTime;

	this->CurrentTime = NewTime;
	this->SpotPrice = SpotPrice;

	//Actualization of dividends
	int OldNext = this->Dividends.get_Next();
	int Periods = this->Dividends.get_Periods();
	int Delta = NewTime - OldTime;

	int NextDividend = (Periods - Delta%Periods + OldNext)%Periods;

	if(NextDividend == 0){
		this->Dividends.set_Next(Periods);
	}else{
		this->Dividends.set_Next(NextDividend);
	}


}

int DividendCounter(int Delta, int Next, int Periods){
	int counter = 0;
	if(Delta >= Next){
		Delta -= Next;
		counter = Delta/Periods + 1;
	}
	return counter;
}



asset Asset_Estimation(int Time, double RiskFreeRate) const{
	asset AssetEstimate = *this;
	// Computation of the expected spot price of the asset at time t=Time
	// Following the dividends type, the pricing is different
	dividend DivAsEs = AssetEstimate.get_Dividends();
	int DivType = DivAsEs.get_Type();
	double ExpectedPrice;
	int OldTime = AssetEstimate.get_CurrentTime();
	int Next = DivAsEs.get_Next();
	double DivRate = DivAsEs.get_Rate();

	if(DivType == 0){ 
		ExpectedPrice = SpotPrice * exp( RiskFreeRate * (Time - OldTime) );
		AssetEstimate.Asset_Actualization(Time, ExpectedPrice);
	}else if(DivType == 1){
		int DivCount = DividendCounter( Time - OldTime, Next);
		ExpectedPrice = SpotPrice * exp( RiskFreeRate * (Time - OldTime)) * pow((1 - DivRate), DivCount);
	}else{
		ExpectedPrice = SpotPrice * exp( (RiskFreeRate - DivRate ) * (Time - OldTime));
	}

	AssetEstimate.Asset_Actualization(Time, ExpectedPrice);
	return AssetEstimate;
}



int main(int argc, char const *argv[])
{
	std::cout << DividendCounter(1, 2, 15) << std::endl;
	return 0;
}






