#include "BlockTypeDatabase.h"

BlockDatabase & BlockDatabase::get()
{
	static BlockDatabase db;
	return db;
}

sf::Color BlockDatabase::getColour(BlockID id)
{
	return _blocks[(int)id];
}

BlockDatabase::BlockDatabase()
{
	_blocks[(int)BlockID::Grass] = sf::Color(0, 255, 0);
	_blocks[(int)BlockID::Sand] = sf::Color(255, 255, 153);
	_blocks[(int)BlockID::Water] = sf::Color(0, 0, 255);
	_blocks[(int)BlockID::Snow] = sf::Color(255, 255, 255);
	_blocks[(int)BlockID::Stone] = sf::Color(192, 192, 192);

}
