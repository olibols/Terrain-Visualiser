#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"
#include <chrono>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed / 2)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z);

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z);

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 60)
		return sf::Color(0, 0, 255);

	if (getHeightAt(x - 1, z) > height || getHeightAt(x, z -1) > height
		|| getHeightAt(x + 1, z) > height || getHeightAt(x, z + 1) > height) {
		colour.r *= height;
		colour.g *= height;
		colour.b *= height;
	}

	return colour;
}

void WorldTerrain::setupGenerators()
{
	NoiseParameters mainParams;
	mainParams.amplitude = 100;
	mainParams.offset = -50;
	mainParams.octaves = 6;
	mainParams.roughness = 0.35;
	mainParams.smoothness = 250;

	_mainHeightmap.setNoiseParameters(mainParams);
}
