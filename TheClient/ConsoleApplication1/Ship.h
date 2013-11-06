#pragma once
#include "actor.h"
#include "Util.h"
#include "Bullet.h"
class Ship :
	public Actor
{
public:
	Ship(void);
	Ship::Ship(int mX, int mY);
	~Ship(void);
	int TargetX;
	int TargetY;
	sf::CircleShape act(EventHandler h);
	sf::CircleShape act();
	sf::CircleShape Ship::act(EventHandler e, Util * u);

private:
	int moveSpeed;
	int health;
};

