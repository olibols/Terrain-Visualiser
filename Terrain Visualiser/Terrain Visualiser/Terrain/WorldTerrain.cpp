#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = (_mainHeightmap.GetValue(x, z) + 1) * 200;

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.GetValue(x, z);

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 60)
		return sf::Color(0, 0, 255);

	colour.r = height * 0.8;
	colour.b = height * 0.8;

	return colour;
}

void WorldTerrain::setupGenerators()
{

}
