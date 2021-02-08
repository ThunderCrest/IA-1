#pragma once

#include "Room.h"
//class Agent

class Effector
{
protected:
	//Agent* agent
public:
	virtual void ExecuteEffector(Room* room) = 0;
};

