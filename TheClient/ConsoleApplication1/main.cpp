// ConsoleApplication1.cpp : Defines the entry point fo		r the console application.
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
	int MAXX = 500;
	int MAXY = 500;
	sf::RenderWindow window(sf::VideoMode(MAXX, MAXY), "SFML works!");
	sf::RenderWindow * point = new sf::RenderWindow();
	// sf::CircleShape shape(100.f);
	// shape.setFillColor(sf::Color::Green);
	Util utils;
	utils.initialize();
	Ship opponentShip;
	EventHandler events;
	sf::Time start(events.myClock.getElapsedTime());
	sf::Time end(events.myClock.getElapsedTime());
	
	Ship playerShip(MAXX, MAXY, events, 0);
	Ship enemyShip(MAXX, MAXY, events, 1);

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

			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				events.mouseRightX = sf::Mouse::getPosition(window).x;
				events.mouseRightY = sf::Mouse::getPosition(window).y;
			}

			events.mouseX = sf::Mouse::getPosition(window).x;
			events.mouseY = sf::Mouse::getPosition(window).y;
			//std::cout << events.mouseRightX << "<" << events.mouseRightY << "\n";
		}
		end = events.myClock.getElapsedTime();
		if(end - start >= sf::milliseconds(15))
		{
			start = end;
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
			//std::cout << "number of things: " << obs << "\n";
			//   window.draw(shape);
			window.display();
		}
	}

	return 0;
}

