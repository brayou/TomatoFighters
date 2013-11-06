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
	first = NULL;
	last = NULL;
	std::cout << "Initializing utils\n";
}

void Util::addBullet(Bullet * b)
{
	
	//std::cout << "Pointer of b:" << b << " and pointer of first:" << first << "\n";
	if(first == NULL)
	{
		
		first = b;
		last = b;
	} else 
	{
		last->next = b;
		b->prev = last;
		last = b;
		//std::cout << "adding a bullet\n";
	}

}

