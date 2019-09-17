#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "../Blocks.h"

class BlockDatabase {
public:
	static BlockDatabase& get();

	sf::Color getColour(BlockID id);

private:

	BlockDatabase();

	std::array<sf::Color, (size_t)BlockID::NUM_TYPES> _blocks;
};