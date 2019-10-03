#include "PerlinNoise.h"
#include "NoiseGenerator.h"

PerlinNoise::PerlinNoise(int seed) : _seed(seed)
{}

double PerlinNoise::GetValue(double x, double z)
{
	auto total = 0.0;

	for (int octave = 0; octave < _octaves - 1; octave++) {
		auto frequency = pow(2.0, octave);
		auto amplitude = pow(_roughness, octave);
		total += noisegen::CoherentValueNoise(((double)x) * frequency / _smoothness,
											  ((double)z) * frequency / _smoothness,
											  _seed) * amplitude;
	}

	auto val = (((total / 2.1) + 1.2) * _amplitudeMultiplier) + _offset;

	return val > 0 ? val : 1;
}

