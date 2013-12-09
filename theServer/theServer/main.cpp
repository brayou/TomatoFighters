// main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "EventHandler.h"
#include "Util.h"
#include <SFML\Network.hpp>
//#include <SFML\Graphics.hpp>
#include <iostream>
#pragma once
using namespace sf;

int main(int argc, char* argv[])
{
	std::cout << "SERVER STARTING UP";
	//declare the UDP socket
	UdpSocket socket;
	//let the socket receive empty packets
	socket.setBlocking(false);
	//let the OS pick a random port
	Socket::AnyPort;
	unsigned short portOut = socket.getLocalPort();
	//bind the socket to the port ***POSSIBLE BREAKPOINT***
	while(socket.bind(portOut) != Socket::Done) socket.bind(portOut);

	unsigned int numClients = 0;
	//declare the input char array and its size (10 chars)
	char keysPressed[] = {255,numClients,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	size_t numKeys = strlen(keysPressed);
	//declare an "IpAddress" that actually messages everyone on the network(LAN)
	IpAddress broadcast = IpAddress::Broadcast;
	//declare my current IpAddress
	IpAddress mine = IpAddress::getLocalAddress();
	//declare the max message size that can be sent or received
	const size_t max = UdpSocket::MaxDatagramSize - 1;
	
	/* NOT NEEDED FOR ONLY 2 CLIENTS
	//Declare an array of IPs
	IpAddress ips[] = {mine};
	//Get the size of the IP array
	const int numIps = sizeof(ips)/sizeof(mine);
	*/
	
	//Initalize the sender's IP and port
	IpAddress sender = IpAddress(0,0,0,0);
	unsigned short portIn;
	//Initialize client 1 and 2's IPs
	IpAddress client1 = IpAddress(0,0,0,0), client2 = IpAddress(0,0,0,0);

	//While esc is not pressed, switch between two states
	//Connecting or Running
	while(true) {
		while(client1.toInteger() == 0 || client2.toInteger() == 0) {
			//Send 255 followed by the number of clients connected
			socket.send(keysPressed,numKeys,broadcast,portOut);
			//Receive null packets from clients that have found us
			socket.receive(keysPressed,max,numKeys,sender,portIn);
			//If we've received something
			if(sender.toInteger() != 0) {
				//If this is the first client to connect
				if(client1.toInteger() == 0) {
					client1 = sender;
					//Change numClients to 1 and recreate the identifier packet
					numClients = 1;
					char keysPressed[] = {255,numClients,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
				}
				else if(client2.toInteger() == 0) {
					client2 = sender;
					numClients = 2;
					char keysPressed[] = {255,numClients,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
				}
			}
			sender = NULL;
		}
		//Clients connected! Now make sure they stay connected
		EventHandler events;
		Time start1(events.myClock.getElapsedTime());
		Time start2(events.myClock.getElapsedTime());
		Time end1(events.myClock.getElapsedTime());
		Time end2(events.myClock.getElapsedTime());

		//LOOP BEGINS
		while(client1.toInteger() != 0 && client2.toInteger() != 0) {
			std::cout << "Clients connected!";
			//Receive keys pressed
			//If no messages received OR if messages are not coming from the clients
			if(socket.receive(keysPressed,max,numKeys,sender,portIn) != Socket::Done || sender != client1 || sender != client2) {
				//Check to make sure each timer does not exceed 250 ms
				//If it does, disconnect that client
				end1 = events.myClock.getElapsedTime();
				if(end1 - start1 >= sf::milliseconds(250)) {
					std::cout << "Client ONE disconnected :(";
					client1 = IpAddress(0,0,0,0);
					break;
				}
				end2 = events.myClock.getElapsedTime();
				if(end2 - start2 >= sf::milliseconds(250)) {
					std::cout << "Client TWO disconnected :(";
					client2 = IpAddress(0,0,0,0);
					break;
				}
			}
			//Otherwise, reset timer X everytime a message is received from client X
			if(sender == client1) start1 = end1 = events.myClock.getElapsedTime();
			if(sender == client2) start2 = end2 = events.myClock.getElapsedTime();

			//CALCULATIONS BELOW

			//END CALCULATIONS
			//SENDING DATA BELOW
			
			//Send the data back to the clients
			socket.send(keysPressed,numKeys,broadcast,portOut);			
		}
	}
	return 0;
}