#include "SnowFlake.h"

SnowFlake::SnowFlake(int id,sf::Vector2f start_position, double V, double P, double L, double R)
{
	f_id = id;
	v = V;
	phase = P;
	lifetime = L;
	position = start_position;
	snowflake.setPosition(position);
	pos = start_position.x;
	vy = 100;
	time = 0;

	snowflake.setRadius(R);
}

SnowFlake::~SnowFlake()
{
}
