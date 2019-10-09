#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>
#include <cmath>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed),
_mountainMap(_seed * 2),
_valleyMap(_seed + 20)
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
	if (height > 65) {
		height *= _mountainMap.GetRidgedHeight(x, z);
	}

	//height -= pow(_valleyMap.GetHeight(x, z), 3) * 100;

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
	_mainHeightmap.GetNoise().SetFractalGain(0.5);
	_mainHeightmap.GetNoise().SetFractalGain(0.3);

	_mountainMap.SetAmplitude(2);
	_mountainMap.SetOffset(1);
	_mountainMap.GetNoise().SetFrequency(0.005);
	_mountainMap.GetNoise().SetFractalOctaves(6);
	_mountainMap.GetNoise().SetFractalGain(0.6);

	_valleyMap.GetNoise().SetNoiseType(FastNoise::NoiseType::Cellular);
	_valleyMap.GetNoise().SetCellularReturnType(FastNoise::CellularReturnType::Distance);
	_valleyMap.SetOffset(0);
	_valleyMap.SetAmplitude(1);
}
