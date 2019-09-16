#pragma once
#include "Terrain\WorldTerrain.h"
#include <SFML/Graphics.hpp>

class Application {
public:

	Application();

	void runLoop();

private:

	WorldTerrain _worldTerrain;
	sf::Image imageBuffer;

};