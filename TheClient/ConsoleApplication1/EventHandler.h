#pragma once
#include "SFML\System.hpp"
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	int mouseLeftX;
	int	mouseRightX;
	int	mouseLeftY;
	int	mouseRightY;
	int mouseX;
	int mouseY;
	int tar [2];
	int * getTarget(int align);
	bool shootNow(int align);
	enum KEYS {space, z, x};
	bool keySwitch [3];
	sf::Clock myClock;
};

