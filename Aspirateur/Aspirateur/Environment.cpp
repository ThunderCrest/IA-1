#include "Environment.h"


Environment::Environment(): m_manor(Manor(5,5))
{
	m_manor = Manor(5, 5);
	m_gameIsRunning = true;
	m_bAlive = true;
}

Environment::~Environment()
{

}

Manor& Environment::getManor()
{
	return m_manor;
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
	int range = Rand(1, 4);
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

void Environment::Run()
{
	while (m_bAlive)
	{
		this->m_lastTickTime = -1;
		while (m_bAlive)
		{
			time(&this->m_currentTickTime);
			if (this->m_currentTickTime - this->m_lastTickTime > 0)
			{
				this->m_lastTickTime = this->m_currentTickTime;
				std::cout << "\x1B[2J\x1B[H";
				std::cout << m_manor << "\n";

				if (shouldThereBeANewDirtySpace() == true)
				{
					int range = 0;
					range = Rand(0, 24);
					m_manor.getRoom(range).setDirt(true);

				}

				if (shouldThereBeANewLostJewel())
				{
					int range = 0;
					range = Rand(0, 24);
					Room* room = &m_manor.getRoom(range);
					room->setJewel(true);

				}

			}



		}
	}
}