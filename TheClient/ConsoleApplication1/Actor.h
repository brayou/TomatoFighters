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
	int getRadius();
	int getAlign();
	virtual sf::Sprite act(EventHandler h);
	virtual sf::Sprite act();
	virtual char getType(); // can change to String if number of types of Actors increases


protected:
	sf::Texture actorTexture;
	sf::Sprite actorSprite;
	int radius;
	sf::Time start;
	sf::Time end;
	int alignment;
	sf::Color myColor;

	

};

