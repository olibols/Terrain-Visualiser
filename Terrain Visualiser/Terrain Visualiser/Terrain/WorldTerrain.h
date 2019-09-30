#pragma once

#include "../Blocks.h"
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

};