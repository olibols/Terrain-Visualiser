#include "Application.h"


Application::Application()
{
	imageBuffer.create(1000, 1000, sf::Color(0, 0, 0));
}

void Application::runLoop()
{
	sf::RenderWindow App(sf::VideoMode(1000, 1000), "Terrain Visualiser");

	for(int x = 0; x < 1000; x++){
		for (int z = 0; z < 1000; z++) {

			int height = _worldTerrain.getHeightAt(x, z);

			if (height < 80)
				imageBuffer.setPixel(x, z, sf::Color(0, 0, 255));
			else
				imageBuffer.setPixel(x, z, sf::Color(0, _worldTerrain.getHeightAt(x, z), 0));
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
		}

		App.clear();
		App.draw(sprite);
		App.display();
	}

}
