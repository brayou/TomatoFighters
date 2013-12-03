// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Util.h"
#include "Ship.h"
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <iostream>
using namespace sf;

void endGameWindow(sf::RenderWindow* window, int winnerAlign)
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window->close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				window->close();
			window->clear();
			sf::Text text;

			sf::Font font;
			font.loadFromFile("arial.ttf");


			// select the font
			text.setFont(font); // font is a sf::Font

			// set the string to display
			std::string s = "The Winner is ";
			if(winnerAlign == 0)
			s += "BLUE!";
			if(winnerAlign == 1)
			s += "GREEN!";
			s+="\n Press space to exit";
			text.setString(s);

			text.setCharacterSize(30); // in pixels

			if(winnerAlign == 0)
			text.setColor(sf::Color::Blue);
			if(winnerAlign == 1)
			text.setColor(sf::Color::Green);

			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
			text.setPosition(10, 100);
			window->draw(text);
			window->display();
		}
	}
}


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

	enemyShip.setHealthPosition(sf::Vector2f(0, window.getSize().y - enemyShip.getHealthBar().getSize().y));
	
	//Set up client networking <------------------>
	//declare the UDP socket
	UdpSocket socket;
	//let the socket receive empty packets
	socket.setBlocking(false);
	//let the OS pick a random port
	Socket::AnyPort;
	unsigned short portOut = socket.getLocalPort();
	//bind the socket to the port
	if(socket.bind(portOut) != Socket::Done) {
		return -1;
	}
	//declare the input char array and its size (10 chars)
	char keysPressed[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	size_t numKeys = strlen(keysPressed);
	//declare my current IpAddress
	IpAddress mine = IpAddress::getLocalAddress();
	//declare the max message size that can be sent or received
	const size_t max = UdpSocket::MaxDatagramSize - 1;
	//Initalize the sender's IP and port
	IpAddress sender;
	unsigned short portIn;
	//Initialize the server's IP
	IpAddress server;
	
	//Halt program until server has been located ***POSSIBLE BREAKPOINT***
	while(sender == NULL) {
		//Receive data
		if(socket.receive(keysPressed,max,numKeys,sender,portIn) != Socket::Done) {
			return -1;
		}
		keysPressed
		//Send identity
		if(socket.send(keysPressed,numKeys,broadcast,portOut) != sf::Socket::Done) {
			return -1;
		}
	}
	//End networking setup <------------------>
	
	//LOOP BEGINS

	//if the message is too big
	if(strlen(keysPressed) > max) {
		//allocate a new array for the remainder of the message and send it
		const size_t remain = strlen(keysPressed) - max;
		char *temp = new char[remain];
		for(unsigned int i = max; i < remain + max; i++) temp[i] = keysPressed[i];
		if(socket.send(temp,max,broadcast,portOut) != sf::Socket::Done) return -1;
		//truncate the old array
		keysPressed[max] = '\0';
	}
	//Send the keys pressed
	if(socket.send(keysPressed,numKeys,broadcast,portOut) != sf::Socket::Done) {
		return -1;
	}
	
	//Receive keys pressed
	if(socket.receive(keysPressed,max,numKeys,sender,portIn) != Socket::Done) {
		return -1;
	}
	

	//main client loop BELOW
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}
			events.keySwitch[events.space] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			events.keySwitch[events.x] = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
			events.keySwitch[events.z] = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
			events.keySwitch[events.w] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			events.keySwitch[events.a] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			events.keySwitch[events.s] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			events.keySwitch[events.d] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			events.keySwitch[events.p] = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
			events.keySwitch[events.e] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
			events.keySwitch[events.r] = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
			events.keySwitch[events.o] = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
			events.keySwitch[events.t] = sf::Keyboard::isKeyPressed(sf::Keyboard::T);
			events.keySwitch[events.i] = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
			events.keySwitch[events.up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
			events.keySwitch[events.down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			events.keySwitch[events.left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
			events.keySwitch[events.right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

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

			//***Send data to theServer
			//BEGIN SENDING DATA TO theServer

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

				//check shield collisions to be added

				if(playerShip.didICollide(cur))
				{
					cur->destroy = true;
					playerShip.gotHitColor();
					if (!playerShip.takeDamage((*cur).getDamage()))
					{
						std::cout << "Green wins!"; //TODO: Customize message & window for winner and loser
						endGameWindow(&window, 1);
						//window.close();
					}
				}

				if(enemyShip.didICollide(cur))
				{
					cur->destroy = true;
					enemyShip.gotHitColor();
					if (!enemyShip.takeDamage((*cur).getDamage()))
					{
						std::cout << "Blue wins!"; 
						endGameWindow(&window, 0);
						//window.close();
					}
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
			//END SENDING DATA TO theServer
			//***Receive data from theServer
			window.draw(playerShip.getHealthBar());
			window.draw(enemyShip.getHealthBar());
			window.draw(playerShip.act(events, &utils));
			window.draw(enemyShip.act(events, &utils));
			// std::cout << "number of things: " << obs << "\n";
			// window.draw(shape);
			window.display();
		}
	}

	return 0;
}

