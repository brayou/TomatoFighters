#pragma once
#include "actor.h"
class Ship :
	public Actor
{
public:
	Ship(void);
	~Ship(void);
	int TargetX;
	int TargetY;
	void act(Util u);
private:
	int moveSpeed;
	int health;
};

