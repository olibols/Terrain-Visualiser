#pragma once
#include <cmath>

namespace noisegen {


	double ValueNoise(int n, int seed);
	double ValueNoise(double x, double y, int seed);

	double CoherentValueNoise(double x, double z, double seed);

	inline double lerp(double a, double b, double z)
	{
		double mu2 = (1 - std::cos(z * 3.14)) / 2;
		return (a * (1 - mu2) + b * mu2);
	}

}