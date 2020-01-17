#include "SnowParticleSystem.h"
#include "SnowFlake.h"

int main()
{
//------tworzy okno i ustawia t³o
	sf::RenderWindow window{ sf::VideoMode{1200, 675}, "Let it snow" };
	window.setFramerateLimit(60);
	sf::Texture texture;
	texture.loadFromFile("background.jpg");
	sf::Sprite background(texture);

	SnowParticleSystem particlesys;

	particlesys.initialize_flakes(window);
	std::cout << window.getSize().y;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		particlesys.fall(window);

		window.clear();
		window.draw(background);

		particlesys.draw(window);

		window.display();
	}
}