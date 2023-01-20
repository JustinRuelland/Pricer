#include <iostream>
#include "asset.h"
// #include <termcolor/termcolor.hpp>

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

dividend& asset::get_alias_Dividends(){
	return this->Dividends;
}

dividend asset::get_Dividends() const{
	return this->Dividends;
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


void asset::Asset_Actualization(double NewTime, double SpotPrice){
	double OldTime = this->CurrentTime;

	this->CurrentTime = NewTime;
	this->SpotPrice = SpotPrice;

	//Actualization of dividends
	double OldNext = this->Dividends.get_Next();
	double Periods = this->Dividends.get_Periods();
	double Delta = NewTime - OldTime;


	if(this->Dividends.get_Type() != 0){
	//double NextDividend = (Periods - Delta%Periods + OldNext)%Periods;
	double NextDividend = modulo((Periods - modulo(Delta, Periods) + OldNext),Periods);

	if(NextDividend == 0.0){
		this->Dividends.set_Next(Periods);
	}else{
		this->Dividends.set_Next(NextDividend);
	}
	}


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


//************** Display overload **************
/*
std::ostream& operator<<(std::ostream& output, const asset& Asset){
	
	char* Name;
	if(Asset.AssetName != nullptr){
		Name = Asset.AssetName;
	}else{
		char EmptyName = '\0';
		Name = &EmptyName;
	}
	
	output << "Asset : " << termcolor::bright_green << Name << "\n - Time (in years) : " << Asset.CurrentTime << "\n - SpotPrice : " << Asset.SpotPrice << "\n - Volatility : " << Asset.Volatility <<"\n";

	if(Asset.Dividends.get_Type() != 0){
		dividend D = Asset.read_Dividends();
		output << termcolor::blue << "===============\n" << "=  Dividends  =\n";
		output << termcolor::blue << " - Rate : " << D.get_Rate() << " \n";
		output << termcolor::blue << " - Periods (in years) : " << D.get_Periods() << " \n";
		output << termcolor::blue << " - Next (in years) : " << D.get_Next() << " \n" << "===============";
	}

	output << termcolor::reset << std::endl;;
	return output;
}
*/
std::ostream& operator<<(std::ostream& output, const asset& Asset){
	
	char* Name;
	if(Asset.AssetName != nullptr){
		Name = Asset.AssetName;
	}else{
		char EmptyName = '\0';
		Name = &EmptyName;
	}
	
	output << "Asset : " << Name << "\n - Time (in years) : " << Asset.CurrentTime << "\n - SpotPrice : " << Asset.SpotPrice << "\n - Volatility : " << Asset.Volatility;

	if(Asset.Dividends.get_Type() != 0){
		dividend D = Asset.get_Dividends();
		output << "\n===============\n" << "=  Dividends  =\n";
		output << " - Rate : " << D.get_Rate() << " \n";
		output << " - Periods (in years) : " << D.get_Periods() << " \n";
		output << " - Next (in years) : " << D.get_Next() << " \n" << "===============";
	}

	output << std::endl;;
	return output;
}


 /*
std::istream& operator>>(std::istream& input, asset& Asset){
	std::cout << " Asset Creation "
}
*/


//************** Tools functions **************

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

int DividendCounter(double Delta, double Next, double Periods){
	return euclidian_division(Delta + Periods - Next, Periods);
}

int euclidian_division(double x, double y){
	return x/y;
}

double modulo(double x, double y){
	return x - (euclidian_division(x,y)*y);
}


int main(int argc, char const *argv[])
{
	
	char name[20];
	std::cin >> name; 
	
	asset Asset1;
	Asset1.get_alias_Dividends().set_Type(1);
	
	Asset1.set_AssetName(name);
	
	Asset1.set_SpotPrice(123.3);

	asset Asset2 = Asset1.Asset_Estimation(100, 0.5);

	std::cout << Asset2 << std::endl;
	return 0;
}






