#include <random>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SnowFlake.h"

const double fps = 1.0 / 60;

double generate_random(double min, double max);

struct optional
{
	double min;
	double max;
};

class Emitter
{
	sf::RectangleShape area;
	sf::Vector2f position;
	
	int e_id;
	
	optional radious;
	optional lifetime;

public:
	int flake_number;
	void replaceFlake(sf::RenderWindow& window, SnowFlake &singleflake);
	void createParticles(sf::RenderWindow& window, std::vector<SnowFlake> &snowflakes,int num);
	Emitter(int id,sf::Vector2f size, sf::Vector2f position, double fnum, sf::Vector2f rad, sf::Vector2f ltime);
	~Emitter();
};

class SnowParticleSystem
{
public:

	std::vector<SnowFlake> snowflakes;
	std::vector<Emitter> emitters;

	double moveX(SnowFlake singleflake);
	void remove(sf::RenderWindow& window, SnowFlake &singleflake, int i);

	SnowParticleSystem();
	void initialize_flakes(sf::RenderWindow& window);
	void fall(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};