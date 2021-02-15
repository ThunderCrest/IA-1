#include "Environment.h"


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
	int range = 0;
	range = min + (int)((float)std::rand() * (max - min + 1) / (RAND_MAX - 1));
	return range;
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
	int range = Rand(1, 20);
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

void Environment::Run()
{
	while (m_bAlive)
	{
		this->m_lastTickTime = -1;
		int currentPositionAgent = 0;
		while (m_bAlive)
		{
			time(&this->m_currentTickTime);
			if (this->m_currentTickTime - this->m_lastTickTime > 0)
			{
				this->m_lastTickTime = this->m_currentTickTime;

				// ajouter la bonne position de l'agent
				for (int i = 0; i < m_manor->getRooms().size(); ++i)
				{
					if (i == currentPositionAgent)
					{
						Room* room = &m_manor->getRoom(i);
						room->setAgent(true);
					}
					else
					{
						Room* room = &m_manor->getRoom(i);
						room->setAgent(false);
					}
				}

				std::cout << "\x1B[2J\x1B[H";
				std::cout << *m_manor << "\n";

				std::cout << m_score;

				if (shouldThereBeANewDirtySpace() == true)
				{
					int range = 0;
					range = Rand(0, 24);
					m_manor->getRoom(range).setDirt(true);

				}

				if (shouldThereBeANewLostJewel() == true)
				{
					int range = 0;
					range = Rand(0, 24);
					Room* room = &m_manor->getRoom(range);
					room->setJewel(true);

				}

			}



		}
	}
}

