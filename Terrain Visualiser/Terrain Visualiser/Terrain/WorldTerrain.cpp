#include "WorldTerrain.h"

WorldTerrain::WorldTerrain() : _seed(120), _dampnessMap(_seed), _mainHeightmap(_seed / 2), _treeMap(_seed / 3)
{
	setupGenerators();
}

BlockID WorldTerrain::getBlockAt(int x, int z)
{
	int dampness = _dampnessMap.getHeight(x, z);

	if (dampness < 80) return BlockID::Sand;

	return BlockID::Grass;
}

int WorldTerrain::getHeightAt(int x, int z)
{
	return _mainHeightmap.getHeight(x, z);
}

void WorldTerrain::setupGenerators()
{
	NoiseParameters dampParams;
	dampParams.amplitude = 70;
	dampParams.offset = 1;
	dampParams.octaves = 6;
	dampParams.roughness = 0.53;
	dampParams.smoothness = 235;

	_dampnessMap.setNoiseParameters(dampParams);


	NoiseParameters mainParams;
	mainParams.amplitude = 70;
	mainParams.offset = 1;
	mainParams.octaves = 6;
	mainParams.roughness = 0.53;
	mainParams.smoothness = 235;

	_mainHeightmap.setNoiseParameters(mainParams);


	NoiseParameters treeParams;
	treeParams.amplitude = 70;
	treeParams.offset = 1;
	treeParams.octaves = 2;
	treeParams.roughness = 0.1;
	treeParams.smoothness = 1;

	_treeMap.setNoiseParameters(treeParams);
}
