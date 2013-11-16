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
	int MAXX = 500; //Window dimensions
	int MAXY = 600;
	sf::RenderWindow window(sf::VideoMode(MAXX, MAXY), "SFML works!");
	sf::RenderWindow * point = new sf::RenderWindow();
	// sf::CircleShape shape(100.f);
	// shape.setFillColor(sf::Color::Green);
	// Utils only has  clock right now, 
	Util utils;
	utils.initialize();
	Ship opponentShip;
	EventHandler events;
	sf::Time start(events.myClock.getElapsedTime());
	sf::Time end(events.myClock.getElapsedTime());
	
	Ship playerShip(MAXX, MAXY, events, 0, sf::Color::Blue);
	Ship enemyShip(MAXX, MAXY, events, 1, sf::Color::Green);

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
				events.keySwitch[events.x] = true;
			} else {
				events.keySwitch[events.x] = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
				events.keySwitch[events.z] = true;
			} else {
				events.keySwitch[events.z] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				events.keySwitch[events.w] = true;
			} else {
				events.keySwitch[events.w] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				events.keySwitch[events.a] = true;
			} else {
				events.keySwitch[events.a] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				events.keySwitch[events.s] = true;
			} else {
				events.keySwitch[events.s] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				events.keySwitch[events.d] = true;
			} else {
				events.keySwitch[events.d] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
				events.keySwitch[events.p] = true;
			} else {
				events.keySwitch[events.p] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				events.keySwitch[events.e] = true;
			} else {
				events.keySwitch[events.e] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				events.keySwitch[events.r] = true;
			} else {
				events.keySwitch[events.r] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
				events.keySwitch[events.o] = true;
			} else {
				events.keySwitch[events.o] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
				events.keySwitch[events.t] = true;
			} else {
				events.keySwitch[events.t] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
				events.keySwitch[events.i] = true;
			} else {
				events.keySwitch[events.i] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				events.keySwitch[events.up] = true;
			} else {
				events.keySwitch[events.up] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				events.keySwitch[events.down] = true;
			} else {
				events.keySwitch[events.down] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				events.keySwitch[events.left] = true;
			} else {
				events.keySwitch[events.left] = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				events.keySwitch[events.right] = true;
			} else {
				events.keySwitch[events.right] = false;
			}


			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				events.mouseRightX = sf::Mouse::getPosition(window).x;
				events.mouseRightY = sf::Mouse::getPosition(window).y;
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				events.mouseLeftX = sf::Mouse::getPosition(window).x;
				events.mouseLeftY = sf::Mouse::getPosition(window).y;
			}
			events.mouseX = sf::Mouse::getPosition(window).x;
			events.mouseY = sf::Mouse::getPosition(window).y;
			//std::cout << events.mouseRightX << "<" << events.mouseRightY << "\n";
		}
		
			events.ally[0] = playerShip.x;
			events.ally[1] = playerShip.y;
			events.opp[0] = enemyShip.x;
			events.opp[1] = enemyShip.y;
		end = events.myClock.getElapsedTime();
		if(end - start >= sf::milliseconds(15))
		{
			start = end;
			window.clear();

			//std::cout << "pointer of first:" << utils.first << "\n";
			Bullet * cur = utils.first;
			Bullet * nex = utils.first;
			int obs = 0;
			playerShip.originColor();
			enemyShip.originColor();
			while(cur != NULL)
			{
				//std::cout << "LOOP\n";
				nex = cur->next;

				window.draw(cur->act());

				//check shield collisions

				if(playerShip.didICollide(cur))
				{
					cur->destroy = true;
					playerShip.gotHitColor();
				}

				if(enemyShip.didICollide(cur))
				{
					cur->destroy = true;
					enemyShip.gotHitColor();
				}

				

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
					cur->~Bullet();
				}
				
			
				obs++;
				cur = nex;
			}
			window.draw(playerShip.act(events, &utils));
			window.draw(enemyShip.act(events, &utils));
			// std::cout << "number of things: " << obs << "\n";
			//   window.draw(shape);
			window.display();
		}
	}

	return 0;
}

