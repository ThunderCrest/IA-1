#include "Room.h"
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>


Room::Room(int x, int y)
{
	// Création d'une pièce avec des coordonées passées en paramètre
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

// Retourne true s'il y a un bijou dans la pièce
bool Room::getJewel() const
{
	return m_jewel;
}
// Idem pour la poussière
bool Room::getDirt() const
{
	return m_dirt;
}
// Idem pour l'agent
bool Room::getAgent() const
{
	return m_agent;
}

// Ajout ou enlève un bijou
void Room::setJewel(bool isPresent)
{
	m_jewel = isPresent;
}
// idem pour la poussière
void Room::setDirt(bool isPresent)
{
	m_dirt = isPresent;
}
// idem pour l'agent
void Room::setAgent(bool isPresent)
{
	m_agent = isPresent;
}

// Permet de tirer un chiffre aléatoirement entre un min et un max
int RandInit(int min, int max)
{
	std::random_device crypto_random_generator;
	std::uniform_int_distribution<int> int_distribution(min, max);
	int result = int_distribution(crypto_random_generator);
	return result;
}

void Room::PickupJewel()
{
	if (m_jewel)
	{
		//Notify jewel pickup
	}
	setJewel(false);
}

// Initie un pièce en lui donnant aléatoirement un bijou et/ ou une pièce (ou aucune des deux)
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