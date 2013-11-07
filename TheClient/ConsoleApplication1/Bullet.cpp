#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(void)
{
}

Bullet::Bullet(double sX, double sY, double sdX, double sdY, int mX, int mY, int align)
{
	radius = 5;
	x = sX;
	y = sY;
	dx = sdX;
	dy = sdY;
	mx = mX;
	my = mY;
	alignment = align;
}

Bullet::~Bullet(void)
{
}

sf::CircleShape Bullet::act()
{
	sf::CircleShape shape(radius *2);
	x += dx;
	y += dy;
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::Red);
	return shape;
}

bool Bullet::deleteMe()
{
	return x>mx || y>my || x+radius*2<0 || y+radius*2<0;
}

