#pragma once

#include "JewelPickupEffector.h"
#include "VacuumEffector.h"

class Manor;

class Agent
{
private:
	JewelPickupEffector jewelPickupEffector;
	VacuumEffector VacuumEffector;

	Manor* manor;

public:

	Agent(Manor* manor);

	void Run();
};

