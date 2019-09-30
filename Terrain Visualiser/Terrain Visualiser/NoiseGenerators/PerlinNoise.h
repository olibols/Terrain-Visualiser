#pragma once

class PerlinNoise {
public:
	PerlinNoise(int seed);

	double GetValue(double x, double y, double z);

	void SetFrequency(double freq);

	void SetLacunarity(double lac);

	void SetOctaveCount(int octavecount);

	void SetPersistence(int persistence);

private:

	double _frequency = 1.0;
	double _lacunarity = 2.0;
	int _octaveCount = 6;
	double _persistence = 0.5;
	
	int _seed = 100;
};