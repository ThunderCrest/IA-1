#include "Room.h"
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>


Room::Room(int x, int y)
{
	// Cr�ation d'une pi�ce avec des coordon�es pass�es en param�tre
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

// Retourne true s'il y a un bijou dans la pi�ce
bool Room::getJewel() const
{
	return m_jewel;
}
// Idem pour la poussi�re
bool Room::getDirt() const
{
	return m_dirt;
}
// Idem pour l'agent
bool Room::getAgent() const
{
	return m_agent;
}

// Ajout ou enl�ve un bijou
void Room::setJewel(bool isPresent)
{
	m_jewel = isPresent;
}
// idem pour la poussi�re
void Room::setDirt(bool isPresent)
{
	m_dirt = isPresent;
}
// idem pour l'agent
void Room::setAgent(bool isPresent)
{
	m_agent = isPresent;
}

// Permet de tirer un chiffre al�atoirement entre un min et un max
int RandInit(int min, int max)
{
	std::random_device crypto_random_generator;
	std::uniform_int_distribution<int> int_distribution(min, max);
	int result = int_distribution(crypto_random_generator);
	return result;
}


// Initie un pi�ce en lui donnant al�atoirement un bijou et/ ou une pi�ce (ou aucune des deux)
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