#pragma once
#include "actor.h"
class Bullet :
	public Actor
{
public:
	Bullet(void);
	Bullet(int sX, int sY, int sdX, int sdY, int mX, int mY);
	~Bullet(void);
	bool isDead;
	Bullet* next;
	Bullet* prev;
	void collide(Actor o);
	sf::CircleShape act();
	void add(Bullet b);
	void removeContacts();
	double dx;
	double dy;
	bool deleteMe();

private:


};

