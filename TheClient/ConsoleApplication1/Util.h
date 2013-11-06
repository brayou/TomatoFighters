#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "Bullet.h" 
#pragma once
class Util
{
	int winX;
	int winY;

public:
	Util(void);
	~Util(void);
	void initialize();
	void addBullet(Bullet * b);
	Bullet* first;
	Bullet* last;


};

