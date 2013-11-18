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
	double x, y;
	int mx, my;
	void getHit(Actor o);
	double getRadius();
	int getAlign();
	virtual sf::Sprite act(EventHandler h);
	virtual sf::Sprite act();


protected:
	sf::Texture actorTexture;
	sf::Sprite actorSprite;
	double radius;
	sf::Time start;
	sf::Time end;
	int alignment;
	sf::Color myColor;

	

};

