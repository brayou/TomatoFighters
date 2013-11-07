#include "stdafx.h"
#include "EventHandler.h"


EventHandler::EventHandler(void)
{
	mouseRightX = 50;
	mouseRightY = 50;
	mouseLeftX = 50;
	mouseLeftY = 50;
}


EventHandler::~EventHandler(void)
{
}

int * EventHandler::getTarget(int align)
{
	if (align == 0)
	{
		tar[0] = mouseRightX;
		tar[1] = mouseRightY;
	} else if (align == 1)
	{
		tar[0] = mouseLeftX;
		tar[1] = mouseLeftY;
	}
	return tar;
}

bool EventHandler::shootNow(int align)
{
	if(align == 0)
		return keySwitch[z];
	if(align == 1)
		return keySwitch[x];

}