#include "stdafx.h"
#include "typeinfo"
#include "Ship.h"
#include <iostream>
#include <cmath>

Ship::Ship(void)
{
}

Ship::Ship(int mX, int mY, EventHandler e, int align, sf::Color c)
{
	mx = mX;
	my = mY;
	x = 50;
	y = std::abs(mx * align - 50);
	health = 100; // arbitrary value
	start = e.myClock.getElapsedTime();
	end = e.myClock.getElapsedTime();
	radius = 20;
	attackDelay = 100;
	curAtkDelay = attackDelay;
	alignment = align;
	myColor = c;
	curColor = c;
	healthBar.setSize(sf::Vector2f(health * 2, 50));
	healthBar.setFillColor(curColor);
	shipTexture.loadFromFile("Me.jpg");
	shipSprite.setTexture(shipTexture);
	shipRenderTexture.create(shipTexture.getSize().x, shipTexture.getSize().y);
	shipRenderTexture.draw(shipSprite);
	sf::CircleShape shape(radius);
	shape.setOutlineColor(curColor);
	shape.setFillColor(sf::Color(0,0,0,0));
	shape.setOutlineThickness(1);
	shipRenderTexture.draw(shape);	
	shipRenderTexture.display(); // update the texture
	shipSprite.setTexture(shipRenderTexture.getTexture());
	hitColor = sf::Color(255-c.r, 255-c.g,255-c.b);
	moveSpeed = 2;
	specialA = 0;
	specialB = 0;
}

Ship::~Ship(void)
{
}

sf::RectangleShape Ship::getHealthBar()
{
	return healthBar;
}

void Ship::setColor(sf::Color color)
{
	healthBar.setFillColor(color);
}

void Ship::setBarriers(std::vector<Barrier> barrierVector)
{
	this->barrierVector = barrierVector;
}

void Ship::setHealthPosition(sf::Vector2f position)
{
	healthBar.setPosition(position);
}

bool Ship::takeDamage(int dmg) // return false if health is less than 0
{
	health -= dmg;
	if (health < 0)
	{
		return false;
	}
	healthBar.setSize(sf::Vector2f(health * 2, 50));
	return true;
}

sf::Sprite Ship::act(EventHandler e)
{
	return shipSprite;
}

sf::Sprite Ship::act()
{
	return shipSprite;
}

void Ship::special(EventHandler e, Util *u)
{
	int dir = -(alignment*2-1);
	char type = e.special(alignment);
	if (type == 'x'||specialA != 0|| specialB != 0 )
		return;
	if (type == 'A')
	{
		curAtkDelay = attackDelay/3;
		specialA = 11;
	}
	if (type == 'B')
	{
		curAtkDelay = attackDelay;
		specialB = 11;
	}
}

Bullet* Ship::generateA(int specialA, int dir)
{
	double dx = (specialA-5.)/6;
	double dy = dir;
	double magnitude = 4/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));

	sf::Color newColor(curColor.r, curColor.g, curColor.b, sf::Int8(180));

	Bullet * mine = new Bullet(x+radius/2, y+radius/2, dx*magnitude,  dy*magnitude, mx, my, alignment, newColor);
	return mine;
}

Bullet* Ship::generateB(int specialB, int dir, EventHandler e)
{
	int * tar = e.getTargetB(alignment);
	double dx = tar[0]+radius/2;
	double dy = tar[1]+radius/2;

	dx = dx-(x+radius/2+(specialB-5.)*10);
	dy = dy-(y+radius/2);
	double magnitude = 4/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));
	sf::Color newColor(curColor.r, curColor.g, curColor.b, sf::Int8(180));

	Bullet * mine = new Bullet(x+radius/2+(specialB-5.)*10, y+radius/2, dx*magnitude,  dy*magnitude, mx, my, alignment, newColor);
	return mine;
}


sf::Sprite Ship::act(EventHandler e, Util* u)
{
	int * tar = e.getTarget(alignment);
	double dx = tar[0];
	double dy = tar[1];

	dx = dx-(x+radius);
	dy = dy-(y+radius);

	if(e.controlScheme == 1)
	{
		//std::cout<<tar[0]<<","<<tar[1]<<"\n";

		dx = tar[0] * moveSpeed;
		dy = tar[1] * moveSpeed;
		//std::cout<<dx<<","<<dy<<"\n";
	}

	double magnitude = 2/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));

	bool hitBarrier = false;
	if(std::abs(dx) > 1 || std::abs(dy) > 1)
	{
		x += dx*magnitude;
		y += dy*magnitude;
		for (int i = 0; i < barrierVector.size() && !hitBarrier; i++) // check barrier collisions
		{
			if (didICollide(&barrierVector.at(i)))
			{
				hitBarrier = true;
			}
		}
	}

	if(x+radius<0 || x+radius > mx || hitBarrier)
		x -= dx*magnitude;
	if(y+radius<0 || y+radius > my || hitBarrier)
		y -= dy*magnitude;
	shipSprite.setPosition(x, y);
	end = e.myClock.getElapsedTime();
	special(e, u);
	if(end - start >= sf::milliseconds(curAtkDelay)) // start bullet creation stuff
	{
		int dir = -(alignment*2-1);
		start = end;

		if(specialA > 0)
		{
			specialA--;
			u->addBullet(generateA(specialA, dir));

		}else if(specialB>0)
		{
			specialB--;	
			u->addBullet(generateB(specialB, dir, e));

		}else if(e.shootNow(alignment))
		{

			//double dx = e.mouseX-(x+radius);
			//double dy = e.mouseY-(y+radius);
			curAtkDelay = attackDelay;
			double dx = 0;
			double dy = dir;
			double magnitude = 4/std::sqrt(std::abs(dx)*std::abs(dx)+std::abs(dy)*std::abs(dy));

			sf::Color newColor(curColor.r, curColor.g, curColor.b, sf::Int8(180));
			Bullet * mine = new Bullet(x+radius/2, y+radius/2, dx*magnitude,  dy*magnitude, mx, my, alignment, newColor);
			u->addBullet(mine);
			

		}
	}
	//std::cout << "pointer of first:" << u.first << "\n";
	return shipSprite;
}

bool Ship::didICollide(Actor * a)
{
	if (a->getType() == 'r') // is a barrier
	{
		int bxLeftBound = a->x - a->getRadius();
		int bxRightBound = a->x + a->getRadius();
		if (x + 2 * radius <= bxLeftBound || x >= bxRightBound) // note that x is the top left corner of the SPRITE not the circle
		{
			return false;
		}
		int byUpBound = a->y - a->getRadius();
		int byDownBound = a->y + a->getRadius();
		if (y + 2 * radius <= byUpBound || y >= byDownBound) // note that y is the top left corner of the sprite
		{
			return false;
		} // TODO: add circular situations
		return true;
	}
	if(a->getAlign() == alignment)
		return false;
	double dist =  distance(a->x + a->getRadius(), a->y + a->getRadius(), x + radius, y + radius); 
	return dist < (a->getRadius() + radius);
}

double Ship::distance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)); 
}

void Ship::gotHitColor()
{
	curColor = hitColor;
}

void Ship::originColor()
{
	curColor = myColor;
}

char Ship::getType()
{
	return 's';
}