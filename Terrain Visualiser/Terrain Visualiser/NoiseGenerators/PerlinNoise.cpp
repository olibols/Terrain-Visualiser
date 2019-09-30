#include "PerlinNoise.h"
#include "NoiseGenerator.h"

PerlinNoise::PerlinNoise(int seed) : _seed(seed)
{}

double PerlinNoise::GetValue(double x, double y, double z)
{
	float total = 0.0;
	float maxAmplitude = 0.0;
	float amplitude = 1.0;
	float frequency = _frequency;

	for (int i = 0; i < _octaveCount; i++) {
		total += noisegen::ValueNoise3D(x * frequency, y * frequency, z * frequency, _seed) * amplitude;
		frequency *= 2.0;
		maxAmplitude += amplitude;
		amplitude *= _persistence;
	}

	return total / maxAmplitude;
}

void PerlinNoise::SetFrequency(double freq)
{
	_frequency = freq;
}

void PerlinNoise::SetLacunarity(double lac)
{
	_lacunarity = lac;
}

void PerlinNoise::SetOctaveCount(int octavecount)
{
	_octaveCount = octavecount;
}

void PerlinNoise::SetPersistence(int persistence)
{
	_persistence = persistence;
}
