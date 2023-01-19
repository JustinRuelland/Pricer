#include <iostream>
#include "asset.h"

//************** Dividend functions **************

// Primary functions

dividend::dividend(){
	this->Type = 0;
	this->Rate = 0.0;
	this->Periods = 0.0;
	this->Next = 0.0;
}

dividend::dividend(int DividendsType, double DividendsRate, double DividendsPeriods, double NextDividend){
	this->Type = DividendsType;
	this->Rate = DividendsRate;
	this->Periods = DividendsPeriods;
	this->Next = modulo(NextDividend, DividendsPeriods);
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

double dividend::get_Periods() const{
	return Periods;
}

double dividend::get_Next() const{
	return Next;
}

void dividend::set_Type(int Type){
	this->Type = Type;
}

void dividend::set_Rate(double Rate){
	this->Rate = Rate;
}

void dividend::set_Periods(double Periods){
	this->Periods = Periods;
}

void dividend::set_Next(double Next){
	this->Next = modulo(Next, this->Periods);
}


//************** Asset functions **************

// Primary functions

asset::asset(){
	dividend Div;

	this->AssetName = nullptr;
	this->CurrentTime = 0.0;
	this->SpotPrice = 0.0;
	this->Volatility = 0.0;
	this->Dividends = Div;
}

asset::asset(char AssetName[20], double CurrentTime, double SpotPrice, double Volatility, dividend Dividends){
	this->AssetName = NameCopie(AssetName);
	this->CurrentTime = CurrentTime;
	this->SpotPrice = SpotPrice;
	this->Volatility = Volatility;
	this->Dividends = Dividends;
}

asset::asset(const asset& Asset1){
	this->AssetName = NameCopie(Asset1.AssetName);
	this->CurrentTime = Asset1.CurrentTime;
	this->SpotPrice = Asset1.SpotPrice;
	this->Volatility = Asset1.Volatility;
	this->Dividends = Asset1.Dividends;
}

asset::~asset(){
	delete[] AssetName;
}


// Basic functions 

char* asset::get_AssetName() const{
	return AssetName;
}

double asset::get_CurrentTime() const{
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

void asset::set_AssetName(char Name[20]){
	if(AssetName != nullptr){
		delete[] AssetName;
	}
	AssetName = NameCopie(Name);
}

void asset::set_CurrentTime(double CurrentTime){
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

int euclidian_division(double x, double y){
	return x/y;
}

double modulo(double x, double y){
	return x - (euclidian_division(x,y)*y);
}

void asset::Asset_Actualization(double NewTime, double SpotPrice){
	double OldTime = this->CurrentTime;

	this->CurrentTime = NewTime;
	this->SpotPrice = SpotPrice;

	//Actualization of dividends
	double OldNext = this->Dividends.get_Next();
	double Periods = this->Dividends.get_Periods();
	double Delta = NewTime - OldTime;



	//double NextDividend = (Periods - Delta%Periods + OldNext)%Periods;
	double NextDividend = modulo((Periods - modulo(Delta, Periods) + OldNext),Periods);

	if(NextDividend == 0.0){
		this->Dividends.set_Next(Periods);
	}else{
		this->Dividends.set_Next(NextDividend);
	}


}

int DividendCounter(double Delta, double Next, double Periods){
	return euclidian_division(Delta + Periods - Next, Periods);
}



asset asset::Asset_Estimation(double Time, double RiskFreeRate) const{
	asset AssetEstimate = *this;
	// Computation of the expected spot price of the asset at time t=Time
	// Following the dividends type, the pricing is different
	dividend DivAsEs = AssetEstimate.get_Dividends();
	int DivType = DivAsEs.get_Type();
	double ExpectedPrice;
	double OldTime = AssetEstimate.get_CurrentTime();
	double Next = DivAsEs.get_Next();
	double DivRate = DivAsEs.get_Rate();
	double Periods = DivAsEs.get_Periods();
	double PriceOldTime = AssetEstimate.get_SpotPrice();

	if(DivType == 0){ 
		ExpectedPrice = PriceOldTime * exp( RiskFreeRate * (Time - OldTime) );
		AssetEstimate.Asset_Actualization(Time, ExpectedPrice);
	}else if(DivType == 1){
		int DivCount = DividendCounter( Time - OldTime, Next, Periods);
		ExpectedPrice = PriceOldTime * exp( RiskFreeRate * (Time - OldTime)) * pow((1 - DivRate), DivCount);
	}else{
		ExpectedPrice = PriceOldTime * exp( (RiskFreeRate - DivRate ) * (Time - OldTime));
	}

	AssetEstimate.Asset_Actualization(Time, ExpectedPrice);
	return AssetEstimate;
}

char* NameCopie(const char chaine[20]){
	char* copie = new char[20];
	bool bufferFull = true;
	for(int i=0; i<19; i++){
		copie[i] = chaine[i];

		if(chaine[i] == '\0'){
			bufferFull = false;
			break;
		}
	}
	if(bufferFull){
		copie[19] = '\0';
	}
	return copie;
}


/*
int main(int argc, char const *argv[])
{
	std::cout << 15%6 << std::endl;
	std::cout << DividendCounter(0.112, 0.10, 0.15) << std::endl;
	return 0;
}

*/




