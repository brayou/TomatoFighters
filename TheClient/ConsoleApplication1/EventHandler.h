#pragma once
#include "SFML\System.hpp"
class EventHandler
{
public:
	EventHandler(void);
	~EventHandler(void);
	int tar [2];
	int ally [2];
	int opp [2];
	int * getTarget(int align);
	int * getTargetB(int align);
	bool shootNow(int align);
	char special(int align);
	enum KEYS {w,a,s,d,i,o,p};
	bool keySwitch [7];
	sf::Clock myClock;
};

