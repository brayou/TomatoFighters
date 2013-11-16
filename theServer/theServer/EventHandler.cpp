#include "stdafx.h"
#include "EventHandler.h"
#include <iostream>


EventHandler::EventHandler(void)
{
	controlScheme = 1;
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
	tar[0] = 0;
	tar[1] = 0;
	if (align == 0 && controlScheme == 0)
	{
		tar[0] = mouseRightX;
		tar[1] = mouseRightY;
	} else if (align == 1 && controlScheme == 0)
	{
		tar[0] = mouseLeftX;
		tar[1] = mouseLeftY;
	} else if (align == 0 && controlScheme == 1)
	{
		if(keySwitch[w])
			tar[1] -= 1;
		if(keySwitch[s])
			tar[1] += 1;
		if(keySwitch[a])
			tar[0] -= 1;
		if(keySwitch[d])
			tar[0] += 1;
			//	std::cout << keySwitch[a] << keySwitch[d] << "\n";

	}else if (align == 1 && controlScheme == 1)
	{
		if(keySwitch[up])
			tar[1] -= 1;
		if(keySwitch[down])
			tar[1] += 1;
		if(keySwitch[left])
			tar[0] -= 1;
		if(keySwitch[right])
			tar[0] += 1;
		//std::cout << keySwitch[left] << keySwitch[right] << "\n";
	}
	return tar;
}

int * EventHandler::getTargetB(int align)
{
	tar[0] = 0;
	tar[1] = 0;
	if (align == 0)
	{
		tar[0] = opp[0];
		tar[1] = opp[1];
	} else if (align == 1)
	{
		tar[0] = ally[0];
		tar[1] = ally[1];
	}
	return tar;
}

bool EventHandler::shootNow(int align)
{
	if(align == 0)
		return keySwitch[e];
	if(align == 1)
		return keySwitch[p];

}

char EventHandler::special(int align)
{
	if(align == 0){
		
		if(keySwitch[r]){
			std::cout<<"here\n";
			return 'A';

		}if(keySwitch[t])
			return 'B';
	}
	if(align == 1){
		if(keySwitch[o])
			return 'A';
		if(keySwitch[i])
			return 'B';
	}
	return 'x';

}