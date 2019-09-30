#include "NoiseGenerator.h"
#include <cmath>

const int X_NOISE_GEN = 1619;
const int Y_NOISE_GEN = 31337;
const int Z_NOISE_GEN = 6971;
const int SEED_NOISE_GEN = 1013;

int noisegen::IntValueNoise3D(int x, int y, int z, int seed)
{
	int n = (
		X_NOISE_GEN    * x
		+ Y_NOISE_GEN * y
		+ Z_NOISE_GEN * z
		+ SEED_NOISE_GEN * seed)
		& 0x7fffffff;
	n = (n >> 13) ^ n;
	return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
}

double noisegen::ValueNoise3D(int x, int y, int z, int seed)
{
	return 1.0 - ((double)IntValueNoise3D(x, y, z, seed) / 1073741824.0);
}

double noisegen::GradientNoise3D(double fx, double fy, double fz, int ix, int iy, int iz, int seed)
{
	return 0.0;
}

double noisegen::GradientCoherentNoise3D(double x, double y, double z, int seed)
{
	return 0.0;
}
