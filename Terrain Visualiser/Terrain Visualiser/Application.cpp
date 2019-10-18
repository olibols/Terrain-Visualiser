#include "Application.h"
#include "Terrain/BlockTypeDatabase.h"

#include <stdio.h>

Application::Application()
{
	imageBuffer.create(1000, 1000, sf::Color(0, 0, 0));
}

void Application::runLoop()
{
	sf::RenderWindow App(sf::VideoMode(1000, 1000), "Terrain Visualiser");

	for(int x = 0; x < 1000; x++){
		for (int z = 0; z < 1000; z++) {
			imageBuffer.setPixel(x, z, _worldTerrain.getColourAt(x * 1.5, z * 1.5));
		}
	}

	sf::Texture temptexture;
	temptexture.create(1000, 1000);
	temptexture.update(imageBuffer);

	sf::Sprite sprite;
	sprite.setTexture(temptexture);


	while (App.isOpen())
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				App.close();
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i position = sf::Mouse::getPosition(App);

				printf("Height: %i \n", _worldTerrain.getHeightAt(position.x, position.y));
			}

		}

		App.clear();
		App.draw(sprite);
		App.display();
	}

}
