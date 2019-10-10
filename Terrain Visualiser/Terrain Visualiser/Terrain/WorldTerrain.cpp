#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>
#include <cmath>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed),
_mountainMap(_seed / 2),
_mountainDistributionMap(_seed + 20)
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
	int mountainHeight = abs(_mountainMap.GetHeight(x, z));
	int distributionMap = _mountainDistributionMap.GetHeight1_0(x, z);

	mountainHeight *= distributionMap;

	height *= mountainHeight + 1;

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 60)
		return sf::Color(0, 0, 255);

	if (height > 130)
		colour = BlockDatabase::get().getColour(BlockID::Snow);

	if (getHeightAt(x - 1, z) > height || getHeightAt(x, z -1) > height) {
		colour.a = 220;
	}

	return colour;
}

void WorldTerrain::setupGenerators()
{
	//_mainHeightmap.SetAmplitude(500);
	_mainHeightmap.GetNoise().SetFractalGain(0.4);

	_mountainMap.GetNoise().SetFrequency(0.005);
	_mountainMap.GetNoise().SetFractalOctaves(6);
	_mountainMap.GetNoise().SetFractalGain(0.5);

	_mountainDistributionMap.GetNoise().SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	_mountainDistributionMap.GetNoise().SetFractalOctaves(2);
	_mountainDistributionMap.GetNoise().SetFrequency(0.006);
}
