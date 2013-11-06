// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Util.h"
#include "Ship.h"
#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	
			std::cout << "I STARTED";
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::RenderWindow * point = new sf::RenderWindow();
   // sf::CircleShape shape(100.f);
   // shape.setFillColor(sf::Color::Green);
	Util utils;
	utils.initialize();
	Ship playerShip(200, 200);
	Ship opponentShip;
	EventHandler events;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				events.keySwitch[events.space] = true;
			} else {
				events.keySwitch[events.space] = false;
			}
			
        }

        window.clear();
		
		window.draw(playerShip.act(events, &utils));
		//std::cout << "pointer of first:" << utils.first << "\n";
		Bullet * cur = utils.first;
		Bullet * nex = utils.first;
		int obs = 0;
		while(cur != NULL)
		{
			//std::cout << "LOOP\n";
			nex = cur->next;
			window.draw(cur->act());
			if(cur->deleteMe())
			{
				if(cur->prev == NULL){
					utils.first = cur->next;
				}else{
					cur->prev->next = cur->next;
				}
				if(cur->next == NULL){
					utils.last = cur->prev;
				}else{
					cur->next->prev = cur->prev;
				}
				cur->prev = NULL;
				cur->next = NULL;
				
			}
			obs++;
			cur = nex;
		}
		std::cout << "number of things: " << obs << "\n";
     //   window.draw(shape);
        window.display();
    }
	
    return 0;
}

