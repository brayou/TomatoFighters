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
	sf::RectangleShape getHealthBar();
	void setColor(sf::Color color);
	void setBarriers(std::vector<Barrier> barrierVector);
	void setHealthPosition(sf::Vector2f position);
	bool takeDamage(int dmg);
	sf::Sprite act(EventHandler h);
	sf::Sprite act();
	sf::Sprite Ship::act(EventHandler e, Util * u);
	void special(EventHandler e, Util * u);
	bool didICollide(Actor * a);
	void gotHitColor();
	void originColor();
	double distance(double x1, double y1, double x2, double y2);
	char getType();
	Bullet* Ship::generateA(int specialA, int dir);
	Bullet* Ship::generateB(int specialB, int dir, EventHandler e);

private:
	int specialA;
	int specialB;
	int moveSpeed;
	int health;
	int attackDelay;
	int curAtkDelay;
	sf::Color hitColor;
	sf::Color curColor;
	sf::RectangleShape healthBar;
	sf::Texture shipTexture;
	sf::Sprite shipSprite;
	sf::RenderTexture shipRenderTexture;
	std::vector<Barrier> barrierVector;
};

