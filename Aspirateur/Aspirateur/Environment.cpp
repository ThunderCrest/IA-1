#include "Environment.h"
#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>


Environment::Environment(Agent* agent, Manor* manor)
{
	// Notre environnement possède un agent et un manoir qu'il récupere lors de son instanciation
	m_manor = manor;
	m_gameIsRunning = true;
	m_bAlive = true;
	m_agent = agent;
	// la mesure de performance commence au nombre de poussière présente dans le manoir et le but de l'agent est de tendre vers 0
	m_score = m_manor->getNotEmptyRoom().size();
}

Environment::~Environment()
{

}

// Récuperation du manoir avec toutes ses pièces
Manor& Environment::getManor()
{
	return *m_manor;
}

// retourne true si le jeu est en marche
bool Environment::gameIsRunning() const
{
	return m_gameIsRunning;
}

// Tire un chiffre au hasard entre une borne min et max
int Rand(int min, int max)
{
	std::random_device crypto_random_generator;
	std::uniform_int_distribution<int> int_distribution(min, max);
	int result = int_distribution(crypto_random_generator);
	return result;
}

// Retourne true si le chiffre 1 a été tiré (probabilité de 1/3 de devoir ajouter une nouvelle poussière)
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

// Retourne true si le chiffre 1 a été tiré (probabilité de 1/15 de devoir ajouter un nouveau bijou)
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

// est appelé à chaque fois que l'agent se déplace ou aspire un bijou
void Environment::increaseScore(int a)
{
	m_score = m_score + a;
}
// est appelé à chaque fois que l'agent aspire une poussière ou ramasse un bijou
void Environment::decreaseScore(int a)
{
	m_score = m_score - a;
}
// retourne la mesure de performance
int Environment::getScore()
{
	return m_score;
}

//Thread environnement
void Environment::run()
{
	this->m_lastTickTime = -1;
	while (m_bAlive)
	{
		time(&this->m_currentTickTime);
		if (this->m_currentTickTime - this->m_lastTickTime > 0)
		{
			this->m_lastTickTime = this->m_currentTickTime;

			// Réaffiche les pièces du manoir et les informations importantes toute les secondes

			std::cout << "\x1B[2J\x1B[H";
			std::cout << *m_manor << "\n";
			std::cout << "mesure de performance: "<< m_score << "\n";
			std::cout << "Methode: " << ((m_agent->getUsingInformedMethod()) ? "Informed" : "Uninformed") << "\n";
			std::cout << "first iteration done: " << ((m_agent->getFirstIterationDone()) ? "true" : "false") << "\n";
			std::cout << "iterations to exploration: " << m_agent->getIterationsToExploration() << "\n";

			// Si les conditions sont remplises, ajout d'une nouvelle poussière dans une pièce vide

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

			// si les conditions sont remplises, ajout d'un nouveau bijou dans une piece vide

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

