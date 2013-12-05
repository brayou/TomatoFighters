#pragma once
#include "actor.h"

class Barrier :
	public Actor
{
public:
	Barrier(void);
	Barrier(int bx, int by, int bRadius);
	Barrier(int bx, int by, int bRadius, sf::Texture bTexture);
	~Barrier(void);
	bool didICollide(Actor* a);
	int howDidICollide(Actor* a);
	char getType();
	sf::Sprite act();
	
private:
	sf::RectangleShape barrierShape;
	sf::Texture barrierTexture;
	sf::Sprite barrierSprite;
};