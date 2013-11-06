#pragma once
#include "actor.h"
#include "Util.h"
class Bullet :
	public Actor
{
public:
	Bullet(void);
	~Bullet(void);
	bool isDead;
	Bullet* next;
	Bullet* prev;
	void collide(Actor o);
	void act(Util u);
	void add(Bullet b);
	void removeContacts();
	double dx;
	double dy;

private:

};

