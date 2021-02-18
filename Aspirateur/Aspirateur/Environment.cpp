#include "Environment.h"
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>


Environment::Environment(Agent* agent, Manor* manor)
{
	m_manor = manor;
	m_gameIsRunning = true;
	m_bAlive = true;
	m_agent = agent;
	m_score = m_manor->getNotEmptyRoom().size();
}

Environment::~Environment()
{

}

Manor& Environment::getManor()
{
	return *m_manor;
}

bool Environment::gameIsRunning() const
{
	return m_gameIsRunning;
}

int Rand(int min, int max)
{
	std::random_device crypto_random_generator;
	std::uniform_int_distribution<int> int_distribution(min, max);
	int result = int_distribution(crypto_random_generator);
	return result;
}

bool Environment::shouldThereBeANewDirtySpace() const 
{
	int range = Rand(1, 3);
	if (range == 1)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Environment::shouldThereBeANewLostJewel() const
{
	int range = Rand(1, 15);
	if (range == 1)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Environment::increaseScore(int a)
{
	m_score = m_score + a;
}
void Environment::decreaseScore(int a)
{
	m_score = m_score - a;
}

int Environment::getScore()
{
	return m_score;
}

void Environment::run()
{
	this->m_lastTickTime = -1;
	while (m_bAlive)
	{
		time(&this->m_currentTickTime);
		if (this->m_currentTickTime - this->m_lastTickTime > 0)
		{
			this->m_lastTickTime = this->m_currentTickTime;

			std::cout << "\x1B[2J\x1B[H";
			std::cout << *m_manor << "\n";
			std::cout << "mesure de performance : "<< m_score << "\n";
			std::cout << "first done: " << m_agent->getFirstIterationDone() << "\n";
			std::cout << "iterations to exploration: " << m_agent->getIterationsToExploration() << "\n";

			if (shouldThereBeANewDirtySpace() == true)
			{
				int range = 0;
				range = Rand(0, 24);
				Room* room = &m_manor->getRoom(range);
				while (room->getDirt() == true)
				{
					range = Rand(0, 24);
					room = &m_manor->getRoom(range);
				}
				room->setDirt(true);
			}

			if (shouldThereBeANewLostJewel() == true)
			{
				int range = 0;
				range = Rand(0, 24);
				Room* room = &m_manor->getRoom(range);
				while (room->getJewel() == true)
				{
					range = Rand(0, 24);
					room = &m_manor->getRoom(range);
				}
				room->setJewel(true);

			}
		}
	}	
}

