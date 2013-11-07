#pragma once
#include "SFML\System.hpp"
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	int mouseLeftX;
	int	mouseRightX;
	int	mouseleftY;
	int	mouseRightY;
	int mouseX;
	int mouseY;
	enum KEYS {space, what};
	bool keySwitch [1];
	sf::Clock myClock;
};

