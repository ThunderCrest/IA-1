#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Room.h"

class Agent;

class Captor
{
	private:
		Agent* _agent;
	public :
		Captor(Agent &agent);
		~Captor() = default;
		int getCurrentRoomIndex();
		int getPerformanceMesure();
		std::vector<Room> getDustyRooms();
		std::vector<Room> getRoomsWithJewel();

// 		std::unique_ptr<Agent> _agent;
		//getNotEmptyRooms
		//getPerformanceMesure from environement 
};

