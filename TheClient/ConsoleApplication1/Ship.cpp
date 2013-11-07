#include "stdafx.h"
#include "Ship.h"
#include <iostream>
#include <cmath>
Ship::Ship(void)
{
}

Ship::Ship(int mX, int mY, EventHandler e, int align)
{
	mx = mX;
	my = mY;
	x = 50;
	y = 50;
	start = e.myClock.getElapsedTime();
	end = e.myClock.getElapsedTime();
	radius = 10;
	attackDelay = 100;
	alignment = align;
}

Ship::~Ship(void)
{
}


sf::CircleShape Ship::act(EventHandler e)
{
	sf::CircleShape shape(radius*2);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}

sf::CircleShape Ship::act()
{
	sf::CircleShape shape(radius*2);
	shape.setFillColor(sf::Color::Blue);
	return shape;
}

sf::CircleShape Ship::act(EventHandler e, Util* u)
{
	
	sf::CircleShape shape(radius*2);
	shape.setFillColor(sf::Color::Blue);
	double dx = e.mouseRightX-(x+radius);
	double dy = e.mouseRightY-(y+radius);
	double magnitude = 2/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));
	if(std::abs(dx) > 1 || std::abs(dy) > 1)
	{
		x += dx*magnitude;
		y += dy*magnitude;
	}
	shape.setPosition(x, y);
	end = e.myClock.getElapsedTime();
	if(end - start >= sf::milliseconds(attackDelay))
	{
		if(e.keySwitch[e.space] == true)
		{	
			start = end;
			double dx = e.mouseX-(x+radius);
			double dy = e.mouseY-(y+radius);
			double magnitude = 4/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));
			Bullet * mine = new Bullet(x+radius, y+radius, dx*magnitude,  dy*magnitude, mx, my, alignment);
			u->addBullet(mine);
		}
	}
	//std::cout << "pointer of first:" << u.first << "\n";
	return shape;
}

bool didICollide(Actor a)
{
}