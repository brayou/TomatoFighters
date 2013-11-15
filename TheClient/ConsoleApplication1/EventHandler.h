#pragma once
#include "SFML\System.hpp"
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	int controlScheme;
	int mouseLeftX;
	int	mouseRightX;
	int	mouseLeftY;
	int	mouseRightY;
	int mouseX;
	int mouseY;
	int tar [2];
	int ally [2];
	int opp [2];
	int * getTarget(int align);
	int * getTargetB(int align);
	bool shootNow(int align);
	char special(int align);
	enum KEYS {space, z, x,w,a,s,d,up,down,left,right, q, e, r, c,y,t,p,o,i,u};
	bool keySwitch [21];
	sf::Clock myClock;
};

