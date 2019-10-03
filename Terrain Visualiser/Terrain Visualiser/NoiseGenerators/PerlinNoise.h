#pragma once

class PerlinNoise {
public:
	PerlinNoise(int seed);

	double GetValue(double x, double z);

	inline void SetOctaves(int octaves) { _octaves = octaves; };
	inline void SetAmplitude(int amp) { _amplitudeMultiplier = amp; };
	inline void SetRoughtness(int roughness) { _amplitudeMultiplier = roughness; };
	inline void SetOffset(int offset) { _offset = offset; };

private:

	int _octaves = 8;
	int _amplitudeMultiplier = 240;
	double _roughness = 0.48;
	int _offset = 0;
	int _smoothness = 190;

	
	int _seed = 100;
};