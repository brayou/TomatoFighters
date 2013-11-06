#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(void)
{
}

Bullet::Bullet(int sX, int sY, int sdX, int sdY, int mX, int mY)
{
	x = sX;
	y = sY;
	dx = sdX;
	dy = sdY;
	mx = mX;
	my = mY;
}

Bullet::~Bullet(void)
{
}

sf::CircleShape Bullet::act()
{
	sf::CircleShape shape(10.f);
	x += dx;
	y += dy;
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Red);
	return shape;
}

bool Bullet::deleteMe()
{
	return x>mx || y>my || x<0 || y<0;
}

