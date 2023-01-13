# include "cdf.h"
#include <iostream>
#include <random>

double cdf(double& d, int& n) {
	std::cout << ("Hello depuis cdf") << std::endl;

	std::default_random_engine generator(time(0));
	std::normal_distribution<double> distribution(0.0, 1.0);

	double sum = 0;
	for (int i = 0; i < n; i++) {
		double x = distribution(generator);
		if (x < d) {
			sum++;
		};
	};

	return sum/n;
};