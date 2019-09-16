#pragma once

#include "../Blocks.h"
#include "NoiseGenerator.h"

class Region;

class WorldTerrain
{
public:
	WorldTerrain();

	BlockID getBlockAt(int x, int z);
	int getHeightAt(int x, int z);

private:

	void setupGenerators();

	int _seed;
	Region* _currentRegion;

	NoiseGenerator _dampnessMap;
	NoiseGenerator _mainHeightmap;
	NoiseGenerator _treeMap;

};