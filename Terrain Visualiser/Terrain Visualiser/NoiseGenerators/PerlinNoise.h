#pragma once

class PerlinNoise {
public:
	PerlinNoise(int seed);

	double GetValue(double x, double z);

	void SetFrequency(double freq);

	void SetOctaveCount(int octavecount);

	void SetPersistence(int persistence);

private:

	double _frequency = 1.0;
	int _octaveCount = 8;
	double _persistence = 0.5;
	
	int _seed = 100;
};