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
#include <vector>

void endGameWindow(sf::RenderWindow* window, int winnerAlign, std::vector<Barrier> barriers)
{
	std::vector<Barrier>().swap(barriers); // deallocate memory by swapping with an empty vector
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
	enemyShip.setHealthPosition(sf::Vector2f(0, window.getSize().y - enemyShip.getHealthBar().getSize().y)); // set the "enemy" health bar to the bottom of the screen
	
	//declare the UDP socket
	UdpSocket socket;
	//let the socket receive even when no packets are there
	socket.setBlocking(false);
	//let the OS pick a random port
	Socket::AnyPort;
	unsigned short portOut = socket.getLocalPort();
	//bind the socket to the port
	if(socket.bind(portOut) != Socket::Done)
		return -1;
	//declare the input char array and its size (20 chars)
	char packet[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	size_t numKeys = strlen(packet);
	//declare my current IpAddress
	IpAddress mine = IpAddress::getLocalAddress();
	//declare the max message size that can be sent or received
	const size_t max = UdpSocket::MaxDatagramSize - 1;
	//Initalize the sender's IP and port
	IpAddress sender = IpAddress(0,0,0,0);
	unsigned short portIn;
	//Initialize the server's IP
	IpAddress server = IpAddress(0,0,0,0);
	//Halt program until server has been located ***POSSIBLE BREAKPOINT***
	
	while(server.toInteger() == 0) {
		//If we receive a packet
		if(socket.receive(packet,max,numKeys,sender,portIn) == Socket::Done) {
			//If it's from the server
			if(packet[0] = 255) {
				server = sender;
				//Try and send the return packet to complete identification
				//If failed, the server will still look for it and will still send out it's 255,NULL packet
				if(socket.send(packet,numKeys,server,portOut) == Socket::Done)
					break;
			}
		}
	}
	
	/*
	// Make barriers
	// All barriers share the same texture for effiency
	int radius = MAXX / 10; // arbitrary barrier radius. The radius is the length of the barrier side.
	sf::RectangleShape barrierShape;
	barrierShape.setSize(sf::Vector2f(2 * radius, 2 * radius));
	barrierShape.setFillColor(sf::Color(128, 64, 0, 255)); // brown
	
	sf::RenderTexture barrierTexture;
	barrierTexture.create(barrierShape.getSize().x, barrierShape.getSize().y);
	barrierTexture.draw(barrierShape);
	barrierTexture.display();
	sf::Texture bTexture = barrierTexture.getTexture();

	int numBarriers = MAXX * MAXY / 40000; // arbitrary number of barriers
	srand(time(NULL)); // different seed each time in order to get different random numbers
	std::vector<Barrier> barrierVector(numBarriers); // create the Barrier array
 	for (int i = 0; i < numBarriers; i++) // set up the Barrier array
	{
		Barrier* newBarrier = new Barrier(std::rand() % MAXX, std::rand() % MAXY, radius, bTexture); // generate a Barrier at a random position
		std::cout << newBarrier->x << " ";
		if (playerShip.didICollide(newBarrier) || enemyShip.didICollide(newBarrier))
		{
			i--; // if the barrier encloses a ship, we do not want it;
		}
		else
		{
			barrierVector[i] = *newBarrier;
		}
	}
	playerShip.setBarriers(barrierVector); // Send the same barrier information to each player
	enemyShip.setBarriers(barrierVector);
	*/

	//BEGIN SENDING DATA TO theServer
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				//***std::vector<Barrier>().swap(barrierVector); // deallocate barrier vector
				window.close();
			}
			events.keySwitch[events.w] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			events.keySwitch[events.a] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			events.keySwitch[events.s] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			events.keySwitch[events.d] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			events.keySwitch[events.i] = sf::Keyboard::isKeyPressed(sf::Keyboard::I);
			events.keySwitch[events.o] = sf::Keyboard::isKeyPressed(sf::Keyboard::O);
			events.keySwitch[events.p] = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
		}
		events.ally[0] = playerShip.x;
		events.ally[1] = playerShip.y;
		events.opp[0] = enemyShip.x;
		events.opp[1] = enemyShip.y;

		/*
		//Send the keys pressed
		if(socket.send(packet,numKeys,server,portOut) != sf::Socket::Done) {
			return -1;
		}
		//Receive keys pressed
		if(socket.receive(packet,max,numKeys,sender,portIn) != Socket::Done) {
			return -1;
		}
		*/
		end = events.myClock.getElapsedTime();
		if(end - start >= sf::milliseconds(15))
		{
			start = end;
			window.clear();
			
			/*// Draw barriers

			for (int i = 0; i < barrierVector.size(); i++)
			{
				window.draw(barrierVector[i].act());
			}
			*/
			

			//std::cout << "pointer of first:" << utils.first << "\n";
			Bullet * cur = utils.firstBullet;
			Bullet * nex = utils.firstBullet;
			int obs = 0;
			playerShip.originColor();
			enemyShip.originColor();
			while(cur != NULL)
			{
				//std::cout << "LOOP\n";
				nex = cur->next;

				window.draw(cur->act());

				//check shield collisions to be added

				/*
				//check barrier collisions

				bool hitBarrier = false;
				for (int i = 0; i < barrierVector.size() && !hitBarrier; i++)
				{
					int collisionValue = barrierVector.at(i).howDidICollide(cur);
					if (collisionValue != -1)
					{
						hitBarrier = true;
						if (collisionValue == 1) // vertical collision. see definition in Barrier class
						{
							cur->setVelocity(-cur->dx, cur->dy); // flip the horizontal velocity
						}
						if (collisionValue == 2) // collisionValue must be 1 or 2. This is the horizontal collision case.
						{
							cur->setVelocity(cur->dx, -cur->dy); // flip the vertical velocity
						}
					}
				}
				*/
				if(playerShip.didICollide(cur))
				{
					cur->destroy = true;
					playerShip.gotHitColor();
					if (!playerShip.takeDamage((*cur).getDamage()))
					{
						std::cout << "Green wins!";
						//endGameWindow(&window, 1, barrierVector);
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
						//endGameWindow(&window, 0, barrierVector);
						//window.close();
					}
				}



				if(cur->deleteMe())
				{
					if(cur->prev == NULL){
						utils.firstBullet = cur->next;
					}else{
						cur->prev->next = cur->next;
					}
					if(cur->next == NULL){
						utils.lastBullet = cur->prev;
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

