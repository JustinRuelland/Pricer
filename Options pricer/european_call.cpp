#include <iostream>
#include "european_call.h"
#include "cdf.h"

void european_call::price(){
	double d_1 = (log(S / K) - (r + pow(sigma, 2) / 2)) / (sigma*sqrt(T));
	double d_2 = d_1 - sigma * sqrt(T);

	int n = 10000;

	double V = S * cdf(d_1, n) - K * exp(-r * T) * cdf(d_2, n);

	std::cout << "Prix du call :" << V << std::endl;
}