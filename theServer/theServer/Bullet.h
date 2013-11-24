#pragma once
#include "actor.h"
class Bullet :
	public Actor
{
public:
	Bullet(void);
	Bullet(double sX, double sY, double sdX, double sdY, int mX, int mY, int align, sf::Color c);
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
	bool destroy;

private:


};

