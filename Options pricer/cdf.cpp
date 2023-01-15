# include "cdf.h"
#include <iostream>
#include <random>

double cdf(double& d) {
	std::default_random_engine generator(time(0));
	std::normal_distribution<double> distribution(0.0, 1.0);

	int n = 100000;

	double sum = 0;
	for (int i = 0; i < n; i++) {
		double x = distribution(generator);
		if (x < d) {
			sum++;
		};
	};

	return sum/n;
};