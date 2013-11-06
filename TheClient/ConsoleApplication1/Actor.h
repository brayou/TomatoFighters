#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#pragma once

class Actor
{
public:
	Actor(void);
	~Actor(void);
	int x, y;
	void getHit(Actor o);
	double getRadius();
	int getAlign();

private:
	double radius;
	sf::Time start;
	sf::Time end;
	int alignment;
	sf::Color c;

};

