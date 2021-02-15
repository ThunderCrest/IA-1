#include "Room.h"
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>


Room::Room(int x, int y)
{
	m_x = x;
	m_y = y;
	m_jewel = false;
	m_dirt = false;
	m_agent = false;

}

Room::~Room()
{

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

bool Room::getAgent() const
{
	return m_agent;
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

int RandInit(int min, int max)
{
	std::random_device crypto_random_generator;
	std::uniform_int_distribution<int> int_distribution(min, max);
	int result = int_distribution(crypto_random_generator);
	return result;
}

void Room::Vacuum()
{
	if (m_dirt) 
	{
		//Notify dirt pickup
	}
	else 
	{
		//Notify dirt pickup error
	}

	if(m_jewel)
	{
		//Notify jewel vacuum
	}
	setDirt(false);
	setJewel(false);
}

void Room::PickupJewel()
{
	if (m_jewel)
	{
		//Notify jewel pickup
	}
	setJewel(false);
}

void Room::initRoom()
{
	int rangeJewel = 0;
	rangeJewel = RandInit(1, 15);
	if (rangeJewel == 1)
	{
		Room::setJewel(true);
	}

	int rangeDirt = 0;
	rangeDirt = RandInit(1, 3);
	if (rangeDirt == 1)
	{
		Room::setDirt(true);
	}
}