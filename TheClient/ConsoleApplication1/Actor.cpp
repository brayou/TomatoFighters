#include "stdafx.h"
#include "Actor.h"


Actor::Actor(void)
{
}


Actor::~Actor(void)
{
}

sf::CircleShape Actor::act(EventHandler e)
{
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}

sf::CircleShape Actor::act()
{
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}