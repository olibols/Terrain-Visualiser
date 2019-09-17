#include "WorldTerrain.h"
#include "BlockTypeDatabase.h"
#include <chrono>

WorldTerrain::WorldTerrain() : _seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())),
_dampnessMap(_seed),
_mainHeightmap(_seed / 2),
_treeMap(_seed / 3),
_riverMap(_seed * 2),
_heatMap(_seed * 3)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z);
	int dampness = _dampnessMap.getHeight(x, z);
	int heat = _heatMap.getHeight(x, z);

	if ((heat < 80 && dampness > 15) || height > 100)
		return BlockID::Snow;

	if (heat > 90 && dampness < 100)
		return BlockID::Sand;

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z);

	if (_riverMap.getHeight(x, z) < 60 && _riverMap.getHeight(x, z) > 50)
		height = 59;

	return height;
}

sf::Color WorldTerrain::getColourAt(int x, int z)
{
	int height = getHeightAt(x, z);
	BlockID block = getBlockAt(x, z);

	sf::Color colour = BlockDatabase::get().getColour(block);

	if (height < 60)
		return sf::Color(0, 0, 255);

	colour.r *= height;
	colour.g *= height;
	colour.b *= height;

	return colour;
}

void WorldTerrain::setupGenerators()
{
	NoiseParameters dampParams;
	dampParams.amplitude = 100;
	dampParams.offset = 50;
	dampParams.octaves = 3;
	dampParams.roughness = 0.53;
	dampParams.smoothness = 235;

	_dampnessMap.setNoiseParameters(dampParams);

	NoiseParameters hotParams;
	hotParams.amplitude = 100;
	hotParams.offset = 50;
	hotParams.octaves = 3;
	hotParams.roughness = 0.53;
	hotParams.smoothness = 235;

	_heatMap.setNoiseParameters(hotParams);

	NoiseParameters mainParams;
	mainParams.amplitude = 100;
	mainParams.offset = -50;
	mainParams.octaves = 9;
	mainParams.roughness = 0.53;
	mainParams.smoothness = 205;

	_mainHeightmap.setNoiseParameters(mainParams);


	NoiseParameters treeParams;
	treeParams.amplitude = 70;
	treeParams.offset = 1;
	treeParams.octaves = 2;
	treeParams.roughness = 0.1;
	treeParams.smoothness = 1;

	_treeMap.setNoiseParameters(treeParams);

	NoiseParameters riverParams;
	riverParams.amplitude = 100;
	riverParams.offset = -50;
	riverParams.octaves = 9;
	riverParams.roughness = 0.53;
	riverParams.smoothness = 205;

	_riverMap.setNoiseParameters(riverParams);
}
