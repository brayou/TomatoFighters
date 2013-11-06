#include "stdafx.h"
#include "Ship.h"
#include <iostream>
Ship::Ship(void)
{
}

Ship::Ship(int mX, int mY)
{
	mx = mX;
	my = mY;
}

Ship::~Ship(void)
{
}


sf::CircleShape Ship::act(EventHandler e)
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}

sf::CircleShape Ship::act()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}

sf::CircleShape Ship::act(EventHandler e, Util* u)
{
	
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Blue);
	if(e.keySwitch[e.space] == true)
	{
		Bullet * mine = new Bullet(10, 10, 1, 1, mx, my);
		u->addBullet(mine);
	}
	//std::cout << "pointer of first:" << u.first << "\n";
	return shape;
}