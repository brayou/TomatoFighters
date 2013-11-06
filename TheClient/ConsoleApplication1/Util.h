#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "Ship.h"
#include "Bullet.h"
#pragma once
class Util
{
	int winX;
	int winY;
	Ship playerShip;
	Ship opponentShip;
	Actor firstOne;
	Actor LastOne;

public:
	Util(void);
	~Util(void);
	int mouseLeftX;
	int	mouseRightX;
	int	mouseleftY;
	int	mouseRightY;
	enum KEYS {up};
	bool keySwitch [1];
	sf::RenderWindow mainWindow;
	void initialize(sf::Window win);
	int methodsYay(int x);
	Ship getMyShip ();


};

