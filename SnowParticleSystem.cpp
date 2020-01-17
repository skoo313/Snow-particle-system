#include "SnowParticleSystem.h"

double generate_random(double min, double max)
{
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}

SnowParticleSystem::SnowParticleSystem()
{
	emitters.push_back(Emitter(0,sf::Vector2f(1200, 100), sf::Vector2f(0, 10), 1000, sf::Vector2f(0.1, 3), sf::Vector2f(10, 30)));
	emitters.push_back(Emitter(1,sf::Vector2f(1200, 100), sf::Vector2f(0, 0), 1000, sf::Vector2f(1, 5), sf::Vector2f(10, 30)));
}

void SnowParticleSystem::initialize_flakes(sf::RenderWindow& window)
{
	for (auto&& e : emitters)
	{
		e.createParticles(window, snowflakes, e.flake_number);
	}
}

double SnowParticleSystem::moveX(SnowFlake singleflake)
{

		double dt = singleflake.time / singleflake.phase;
		return dt < 0.5 ? (singleflake.pos + singleflake.v * (2 * dt*dt)) : (singleflake.pos + singleflake.v * (2 * dt*(2 - dt) - 1));
	
}

void SnowParticleSystem::fall(sf::RenderWindow& window)
{
	for (auto&& singleflake : snowflakes)
	{
		double dt = 0.01;
		singleflake.time += fps;
		singleflake.lifetime -= fps;

		double scale = singleflake.lifetime / 10;

		if (scale < 1)
			singleflake.snowflake.setScale(scale, scale);

		if (singleflake.time > singleflake.phase)
		{
			singleflake.pos += singleflake.v;
			singleflake.v = generate_random(-50, 50);
			singleflake.time = 0.0;
		}

		singleflake.position.x = moveX(singleflake);

		double r = singleflake.snowflake.getRadius();

		//gęstosc sniegu (g/cm3) 
		double p = 0.1;
		//gestosc powietrza (g/cm3) 
		double p0 = 0.0012;

		//wspolczynnik oporu
		double C = 0.47;

		//pole powierzchni na którą działa siła
		double A = 3.14*pow(r, 2);
		//masa płatka
		double m = 4 / 3 * 3.14*pow(r, 3);
		m = m * p;
		//Opór powietrza
		double Fair = 0.5*p0*A*C*pow((singleflake.vy), 2);
		//Przyciąf
		double Fg = 9.81*m;

		singleflake.position.y = singleflake.snowflake.getPosition().y;

		singleflake.vy = singleflake.vy - Fair + Fg;
		singleflake.position.y = singleflake.position.y + (singleflake.vy / m) * dt;

		if (singleflake.position.y > window.getSize().y || singleflake.lifetime <= 0)
			remove(window,singleflake, 1);

		singleflake.snowflake.setPosition(singleflake.position);
	}
}
void SnowParticleSystem::draw(sf::RenderWindow& window)
{ 
	for (auto&& singleflake : snowflakes)
	{

		window.draw(singleflake.snowflake);
	}
}

void SnowParticleSystem::remove(sf::RenderWindow& window, SnowFlake &singleflake, int i)
{
	emitters[singleflake.f_id].replaceFlake(window, singleflake);
}  


Emitter::Emitter(int id, sf::Vector2f size, sf::Vector2f position, double fnum, sf::Vector2f rad, sf::Vector2f ltime)
	:flake_number(fnum)
{
	e_id = id;

	area.setSize(sf::Vector2f(size.x, size.y));
	area.setPosition(position.x, position.y - area.getGlobalBounds().height);

	radious.min = rad.x;
	radious.max = rad.y;

	lifetime.min = ltime.x;
	lifetime.max = ltime.y;

	//snowflakes.reserve(flake_number);
}

void Emitter::createParticles(sf::RenderWindow& window, std::vector<SnowFlake> &snowflakes, int num)
{
	for (int i = 0; i <= num; i++)
	{
		double x = generate_random(0, window.getSize().x);
		double y = generate_random(0, window.getSize().y) - 20;

		sf::Vector2f start_position(x, y);
		snowflakes.push_back(SnowFlake(e_id,start_position, generate_random(-50, 50), generate_random(1, 5), generate_random(lifetime.min, lifetime.max), generate_random(radious.min, radious.max)));
	}
}
void Emitter::replaceFlake(sf::RenderWindow& window, SnowFlake &singleflake)
{
	singleflake.v = generate_random(-50, 50);
	singleflake.phase = generate_random(1, 5);
	singleflake.lifetime = generate_random(lifetime.min, lifetime.max);

	double x =generate_random(0, window.getSize().x);
	double y = generate_random(-10, -50);
	singleflake.position.x = x;
	singleflake.position.y = y;
	singleflake.snowflake.setPosition(singleflake.position);

	singleflake.time = 0;
	singleflake.vy = 100;
	singleflake.snowflake.setScale(	1, 1);

	singleflake.snowflake.setRadius(generate_random(radious.min, radious.max));
}

Emitter::~Emitter()
{
}
