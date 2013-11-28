#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(void)
{
}

Bullet::Bullet(double sX, double sY, double sdX, double sdY, int mX, int mY, int align, sf::Color c)
{
	radius = 10;
	x = sX;
	y = sY;
	dx = sdX;
	dy = sdY;
	mx = mX;
	my = mY;
	damage = 5; // default damage
	alignment = align;
	myColor = c;
	destroy = false;
	bulletTexture.loadFromFile("Dessert.jpg", sf::IntRect(0, 0, 10, 10));
	bulletSprite.setTexture(bulletTexture);
}

Bullet::~Bullet(void)
{
}

void Bullet::setDamage(int dmg)
{
	damage = dmg;
}

int Bullet::getDamage()
{
	return damage;
}

sf::Sprite Bullet::act()
{
	x += dx;
	y += dy;
	bulletSprite.setPosition(x, y);
	return bulletSprite;
}

bool Bullet::deleteMe()
{
	return x>mx || y>my || x+radius*2<0 || y+radius*2<0 || destroy;
}

