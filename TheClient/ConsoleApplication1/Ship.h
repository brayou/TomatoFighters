#pragma once
#include "actor.h"
#include "Util.h"
#include "Bullet.h"
class Ship :
	public Actor
{
public:
	Ship(void);
	Ship::Ship(int mX, int mY, EventHandler e, int align, sf::Color c);
	~Ship(void);
	int TargetX;
	int TargetY;
	sf::Sprite act(EventHandler h);
	sf::Sprite act();
	sf::Sprite Ship::act(EventHandler e, Util * u);
	bool didICollide(Actor * a);
	void gotHitColor();
	void originColor();

private:
	int moveSpeed;
	int health;
	int attackDelay;
	sf::Color hitColor;
	sf::Color curColor;
	sf::Texture shipTexture;
	sf::Sprite shipSprite;
};

