#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "EventHandler.h"
#pragma once

class Actor
{
public:
	Actor(void);
	~Actor(void);
	int x, y;
	int mx, my;
	void getHit(Actor o);
	double getRadius();
	int getAlign();
	virtual sf::CircleShape act(EventHandler h);
	virtual sf::CircleShape act();


private:
	double radius;
	sf::Time start;
	sf::Time end;
	int alignment;
	sf::Color c;

};

