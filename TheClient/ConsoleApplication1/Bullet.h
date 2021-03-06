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

	void setDamage(int dmg);
	int getDamage();
	sf::Sprite act();
	char getType();
	void add(Bullet b);
	void removeContacts();
	double dx;
	double dy;
	void setVelocity(double dx, double dy);
	bool deleteMe();
	bool destroy;

private:
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	int damage;
	int life;

};

