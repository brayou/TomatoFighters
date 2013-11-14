#include "stdafx.h"
#include "Ship.h"
#include <iostream>
#include <cmath>

// test push from my local clone - Ren-Jay

Ship::Ship(void)
{
}

Ship::Ship(int mX, int mY, EventHandler e, int align, sf::Color c)
{
	mx = mX;
	my = mY;
	x = 50;
	y = 50;
	start = e.myClock.getElapsedTime();
	end = e.myClock.getElapsedTime();
	radius = 20;
	attackDelay = 100;
	alignment = align;
	myColor = c;
	curColor = c;
	hitColor = sf::Color(255-c.r, 255-c.r,255-c.r);
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
	
	sf::CircleShape shape(radius);
	shape.setFillColor(curColor);
	int * tar = e.getTarget(alignment);
	double dx = tar[0];
	double dy = tar[1];
	
	dx = dx-(x+radius);
	dy = dy-(y+radius);
	
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
		if(e.shootNow(alignment))
		{	
			//start = end;
			double dx = e.mouseX-(x+radius);
			double dy = e.mouseY-(y+radius);
			double magnitude = 4/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));

			sf::Color newColor(myColor.r, myColor.g, myColor.b, sf::Int8(180));

			Bullet * mine = new Bullet(x+radius, y+radius, dx*magnitude,  dy*magnitude, mx, my, alignment, newColor);
			u->addBullet(mine);
		}
	}
	//std::cout << "pointer of first:" << u.first << "\n";
	return shape;
}

bool Ship::didICollide(Actor * a)
{
	if(a->getAlign() == alignment)
		return false;
	double dist =  std::sqrt(std::pow(a->x + a->getRadius()- x - radius, 2) + std::pow(a->y + a->getRadius() - y - radius, 2)); 
	return dist < (a->getRadius() + radius);
}

void Ship::gotHitColor()
{
	curColor = hitColor;
}

void Ship::originColor()
{
	curColor = myColor;
}
