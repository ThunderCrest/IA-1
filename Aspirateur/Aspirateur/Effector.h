#pragma once

#include "Room.h"
#include <vector>

//class Agent


	class Agent; //Forward Declaration
	enum class actions {
		goRight,
		goLeft,
		goTop,
		goBottom,
		pick,
		aspirate,
		none
	};


	class Effector
	{
	private:
		Agent *_agent;
	public:
		Effector(Agent &agent);
		~Effector()=default;
		void executeAction(actions action);
		void executeActions(std::vector<actions> &actions); //vector of int represent vector of actions
		void goRight();
		void goLeft();
		void goTop();
		void goBottom();
		void aspirate();
		void pick();
		//move(direction)
		//aspirate
		//pick
	};

