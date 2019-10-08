#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed),
_mountainMap(_seed * 2)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = _mainHeightmap.GetHeight(x, z);

	if (height < 65) {
		return BlockID::Sand;
	}

	if (height > 150) {
		return BlockID::Snow;
	}

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.GetHeight(x, z);

	height *= _mountainMap.GetRidgedHeight(x, z);

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 60)
		return sf::Color(0, 0, 255);

	if (getHeightAt(x - 1, z) > height || getHeightAt(x, z -1) > height) {
		colour.a = 220;
	}

	return colour;
}

void WorldTerrain::setupGenerators()
{
	_mountainMap.SetAmplitude(2);
	_mountainMap.SetOffset(1);
	_mountainMap.GetNoise().SetFractalOctaves(6);
	_mountainMap.GetNoise().SetFractalGain(0.5);
}
