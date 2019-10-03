#include "NoiseGenerator.h"
#include <cmath>

const int X_NOISE_GEN = 1619;
const int Y_NOISE_GEN = 31337;
const int Z_NOISE_GEN = 6971;
const int SEED_NOISE_GEN = 1013;

double noisegen::ValueNoise(int n, int seed)
{
	n += seed;
	n = (n << 13) ^ n;
	auto nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

double noisegen::ValueNoise(double x, double y, int seed)
{
	return ValueNoise(x + y * 57, seed);
}

double noisegen::CoherentValueNoise(double x, double z, double seed)
{
	auto floorX = (double)((int)x);
	auto floorZ = (double)((int)z);

	auto    s = 0.0,
			t = 0.0,
			u = 0.0,
			v = 0.0;

	s = ValueNoise(floorX, floorZ, seed);
	t = ValueNoise(floorX + 1, floorZ, seed);
	u = ValueNoise(floorX, floorZ + 1, seed);
	v = ValueNoise(floorX + 1, floorZ + 1, seed);

	auto rec1 = lerp(s, t, x - floorX);
	auto rec2 = lerp(u, v, x - floorX);
	auto rec3 = lerp(rec1, rec2, z - floorZ);
	return rec3;
}



