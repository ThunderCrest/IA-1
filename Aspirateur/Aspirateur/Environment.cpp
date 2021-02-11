#include "Environment.h"

Environment::Environment(): m_manor(Manor(5,5))
{
	m_manor = Manor(5, 5);
	m_gameIsRunning = true;
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