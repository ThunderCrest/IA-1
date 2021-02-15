#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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
// 		std::unique_ptr<Agent> _agent;
		//getNotEmptyRooms
		//getPerformanceMesure from environement 
};

