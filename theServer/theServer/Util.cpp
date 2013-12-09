#include "stdafx.h"
#include "Util.h"
#include <iostream>


Util::Util(void)
{
	
}


Util::~Util(void)
{
}

void Util::initialize()
{
	firstBullet = NULL;
	lastBullet = NULL;
	std::cout << "Initializing utils\n";
}

void Util::addBullet(Bullet * b)
{
	
	//std::cout << "Pointer of b:" << b << " and pointer of first:" << first << "\n";
	if(firstBullet == NULL)
	{
		firstBullet = b;
		lastBullet = b;
	} else 
	{
		lastBullet->next = b;
		b->prev = lastBullet;
		lastBullet = b;
	}

}


