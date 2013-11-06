#include "stdafx.h"
#include "Ship.h"
#include "Util.h"


Ship::Ship(void)
{
}


Ship::~Ship(void)
{
}


void Ship::act(Util u)
{
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Blue);
	u.mainWindow.draw(shape);
}