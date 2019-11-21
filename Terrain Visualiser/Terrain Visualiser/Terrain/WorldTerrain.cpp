#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>
#include <cmath>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed),
_largeElevation(_seed * 2)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	float height = getHeightAt(x, z);

	if (height < 53) {
		return BlockID::Sand;
	}

	if (height > 150) {
		return BlockID::Snow;
	}

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	float height = _mainHeightmap.GetHeight(x, z);

	height *= 1 + pow(_largeElevation.GetHeight1_0(x, z) * 1.2, 3);

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	float height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 50)
		return sf::Color(0, 0, 255);

	if (height > 120)
		colour = BlockDatabase::get().getColour(BlockID::Snow);

	if (getHeightAt(x - 1, z) > height || getHeightAt(x, z -1) > height) {
		colour.a -= 70;
	}

	return colour;
}

void WorldTerrain::setupGenerators()
{
	_mainHeightmap.SetAmplitude(30);
	_mainHeightmap.SetOffset(30);
	_mainHeightmap.GetNoise().SetFractalGain(0.3);

	_largeElevation.GetNoise().SetFrequency(0.002);
	_largeElevation.GetNoise().SetFractalGain(0.1);
	_largeElevation.GetNoise().SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	_largeElevation.GetNoise().SetFractalOctaves(2);
}
