#include <random>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>


class SnowFlake
{
public:
	sf::Vector2f position;
	int f_id;
	double pos;
	double v;
	double vy;
	double phase;
	double time;
	double lifetime;
	sf::CircleShape snowflake;


	SnowFlake(int id,sf::Vector2f start_position, double v = 25, double P = 3, double L = 20, double R = 1);
	~SnowFlake();
};

