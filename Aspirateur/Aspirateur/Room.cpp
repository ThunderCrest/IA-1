#include "Room.h"
#include <iostream>

Room::Room(int x, int y)
{
	m_x = x;
	m_y = y;
	m_jewel = false;
	m_dirt = false;
	m_agent = false;

}

int Room::getX() const
{
	return m_x;
}

int Room::getY() const
{
	return m_y;
}

bool Room::getJewel() const
{
	return m_jewel;
}

bool Room::getDirt() const
{
	return m_dirt;
}

void Room::setJewel(bool isPresent)
{
	m_jewel = isPresent;
}

void Room::setDirt(bool isPresent)
{
	m_dirt = isPresent;
}

void Room::setAgent(bool isPresent)
{
	m_agent = isPresent;
}

int Rand(int min, int max)
{
	int range = 0;
	range = min + (int)((float)std::rand() * (max - min + 1) / (RAND_MAX - 1));
	return range;
}

void Room::initRoom()
{
	int rangeJewel = 0;
	rangeJewel = Rand(1, 20);
	if (rangeJewel == 1)
	{
		Room::setJewel(true);
	}

	int rangeDirt = 0;
	rangeDirt = Rand(1, 2);
	if (rangeDirt == 1)
	{
		Room::setDirt(true);
	}
}