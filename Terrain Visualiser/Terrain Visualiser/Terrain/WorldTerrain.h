#pragma once
#include "../Blocks.h"
#include "../NoiseGenerators/NoiseWrapper.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class Region;

class WorldTerrain
{
public:
	WorldTerrain();

	BlockID getBlockAt(int x, int z);
	int getHeightAt(int x, int z);

	sf::Color getColourAt(int x, int z);

private:

	void setupGenerators();

	int _seed;
	Region* _currentRegion;

	NoiseWrapper _mainHeightmap;
	NoiseWrapper _mountainMap;
	NoiseWrapper _valleyMap;
};