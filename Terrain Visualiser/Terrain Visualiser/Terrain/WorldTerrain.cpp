#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"

#include <chrono>
#include <cmath>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_mainHeightmap(_seed),
_cellHeightmap(_seed * 2)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = getHeightAt(x, z);

	//if (height < 65) {
	//	return BlockID::Sand;
	//}

	if (height > 150) {
		return BlockID::Snow;
	}

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.GetHeight(x, z);

	height *= _cellHeightmap.GetHeight1_0(x, z);

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

	//if(height < )

	if (getHeightAt(x - 1, z) > height || getHeightAt(x, z -1) > height) {
		colour.a -= 30;
	}

	return colour;
}

void WorldTerrain::setupGenerators()
{
	//_mainHeightmap.SetAmplitude(500);
	_mainHeightmap.GetNoise().SetFractalGain(0.4);

	_cellHeightmap.GetNoise();
	_cellHeightmap.GetNoise().SetNoiseType(FastNoise::NoiseType::Cellular);
	_cellHeightmap.GetNoise().SetCellularDistanceFunction(FastNoise::CellularDistanceFunction::Manhattan);
	_cellHeightmap.GetNoise().SetCellularReturnType(FastNoise::CellularReturnType::CellValue);
	_cellHeightmap.GetNoise().SetCellularJitter(0.4);
}
