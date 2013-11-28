#include "stdafx.h"
#include "Actor.h"


Actor::Actor(void)
{
	actorTexture.create(100, 100);
	sf::Uint8 pixels[100 * 100 * 4]; // arbitrary 100 x 100 size
	for (int i = 0; i < 100; i++)
	{
		pixels[i * 4] = 0;
		pixels[i * 4 + 1] = 0;
		pixels[i * 4 + 2] = 255; // turn it blue
		pixels[i * 4 + 3] = 255; // give it maximum opacity
	}
	actorTexture.update(pixels);
	actorSprite.setTexture(actorTexture);
}


Actor::~Actor(void)
{
}

sf::Sprite Actor::act(EventHandler e)
{
	return actorSprite;
}

sf::Sprite Actor::act()
{
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