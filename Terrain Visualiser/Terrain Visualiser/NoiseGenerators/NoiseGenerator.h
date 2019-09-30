#pragma once
#include <cmath>

namespace noisegen {


	int IntValueNoise3D(int x, int y, int z, int seed);
	double ValueNoise3D(int x, int y, int z, int seed);

	double GradientNoise3D(double fx, double fy, double fz, int ix,
		int iy, int iz, int seed);
	double GradientCoherentNoise3D(double x, double y, double z, int seed);

	inline double MakeInt32Range(double n) // Taken from https://github.com/qknight/libnoise/blob/master/src/noise/noisegen.h
	{
		if (n >= 1073741824.0) {
			return (2.0 * fmod(n, 1073741824.0)) - 1073741824.0;
		}
		else if (n <= -1073741824.0) {
			return (2.0 * fmod(n, 1073741824.0)) + 1073741824.0;
		}
		else {
			return n;
		}
	}
}