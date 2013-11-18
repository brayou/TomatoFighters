#include "stdafx.h"
#include "Actor.h"


Actor::Actor(void)
{
	actorTexture.loadFromFile("Kirby.jpg", sf::IntRect(0, 0, 10, 10));
	actorSprite.setTexture(actorTexture);
}


Actor::~Actor(void)
{
}

sf::Sprite Actor::act(EventHandler e)
{
	/*
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
	*/
	return actorSprite;
}

sf::Sprite Actor::act()
{
	/*
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
	*/
	return actorSprite;
}

double Actor::getRadius()
{
	return radius;
}
int Actor::getAlign()
{
	return alignment;
}