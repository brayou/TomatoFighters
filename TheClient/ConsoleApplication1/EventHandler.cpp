#include "stdafx.h"
#include "EventHandler.h"
#include <iostream>


EventHandler::EventHandler(void)
{
	for(int i = 0; i < (sizeof(keySwitch)/sizeof(*keySwitch)); i++)
		keySwitch[i] = false;
	{
	}
}

EventHandler::~EventHandler(void)
{
}

int * EventHandler::getTarget()
{
	tar[0] = 0;
	tar[1] = 0;
	if(keySwitch[w])
		tar[1] -= 1;
	if(keySwitch[s])
		tar[1] += 1;
	if(keySwitch[a])
		tar[0] -= 1;
	if(keySwitch[d])
		tar[0] += 1;
	//	std::cout << keySwitch[a] << keySwitch[d] << "\n";
	return tar;
}

int * EventHandler::getTargetB(int align)//stuff for aiming bullets in special attack b
{
	tar[0] = ally[0];
	tar[1] = ally[1];
	return tar;
}

bool EventHandler::shootNow(int align)
{
	return keySwitch[i];
}

char EventHandler::special(int align)
{
	if(keySwitch[o])
		return 'A';
	if(keySwitch[p])
		return 'B';
	return 'x';
}