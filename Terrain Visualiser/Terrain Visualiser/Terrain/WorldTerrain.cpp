#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"
#include "../NoiseGenerators/NoiseGenerator.h"

#include <chrono>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = noisegen::ValueNoise3D(x, z, 0, _seed);

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = ((noisegen::ValueNoise3D(x, z, 0, _seed) + 1) * 200);

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	//if (height < 60)
	//	return sf::Color(0, 0, 255);

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

}
