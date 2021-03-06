#include "stdafx.h"
#include "Barrier.h"

#include <iostream>

Barrier::Barrier(void)
{
}

Barrier::Barrier(int bx, int by, int bRadius)
{
	x = bx; 
	y = by;
	radius = bRadius;
	barrierShape.setSize(sf::Vector2f(2 * radius, 2 * radius));
	barrierShape.setFillColor(sf::Color(128, 64, 0, 255)); // brown
	
	sf::RenderTexture barrierRTexture;
	barrierRTexture.create(barrierShape.getSize().x, barrierShape.getSize().y);
	barrierRTexture.draw(barrierShape);
	barrierRTexture.display();
	barrierSprite = sf::Sprite(barrierRTexture.getTexture());
	barrierSprite.setPosition(bx - radius, by - radius);
}

Barrier::Barrier(int bx, int by, int bRadius, sf::Texture bTexture) // for efficiency
{
	x = bx; // center x
	y = by; // center y
	radius = bRadius;
	barrierTexture = bTexture;
	barrierSprite = sf::Sprite(barrierTexture);
	barrierSprite.setPosition(bx - radius, by - radius);
}

Barrier::~Barrier(void)
{
}

char Barrier::getType()
{
	return 'r';
}

sf::Sprite Barrier::act()
{
	return barrierSprite;
}

bool Barrier::didICollide(Actor* a) // given x and y are the center of a circle. it is treated like a rectangle
{
	int bxLeftBound = x - radius;
	int bxRightBound = x + getRadius();
	if (a->x + a->getRadius() <= bxLeftBound || a->x - a->getRadius() >= bxRightBound) // note that x is the top left corner of the SPRITE not the circle
	{
		return false;
	}
	int byUpBound = y - radius;
	int byDownBound = y + radius;
	if (a->y + a->getRadius() <= byUpBound || a->y - a->getRadius() >= byDownBound) // note that y is the top left corner of the sprite
	{
		return false;
	} // TODO: add circular situations
	return true;
}

int Barrier::howDidICollide(Actor* a) //-1 indicates no collision. 1 indicates a collision with a vertical surface. 2 indicates a collision with a horizontal surface
{
	if (!Barrier::didICollide(a)) return -1;
	int bxLeftBound = x - radius;
	int bxRightBound = x + getRadius();
	int bxUpBound = y - radius;
	int bxDownBound = y + getRadius();

	if ((a->x + a->getRadius() > bxLeftBound|| a->x - a->getRadius()< bxRightBound) && (std::abs(a->y - bxUpBound) < a->getRadius() || std::abs(a->y - bxDownBound) < a->getRadius() ))
	{
		return 1; // vertical collision
	}
/*	
	if (a->y + a->getRadius()*2 + 1 > bxUpBound|| a->y - a->getRadius()*2 - 1 < bxDownBound)
	{
		return 2; // Horizontal collision
	} */
	return 2; // otherwise is Horizontal
}
