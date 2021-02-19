#include "Captor.h"
#include "Agent.h"
#include "Environment.h"
	Captor::Captor(Agent &agent)
	{
		this->_agent = &agent;
	}


	//Récupère l'index de la salle où l'agent est présent
	int Captor::getCurrentRoomIndex()
	{
		int index = 0;

			for (auto& room : this->_agent->beliefs.m_manor->getRooms())
			{
				if (room.getAgent() == true)
				{
					return index;
				}
				index++;
			}
		return -1 ;
	}

	//Récupère les pièces avec de la poussière 
	std::vector<Room*> Captor::getDustyRooms()
	{
		std::vector<Room*> dustyRooms;
		for (auto& room : this->_agent->beliefs.m_manor->getRooms())
		{
			if (room.getDirt() == true)
			{
				dustyRooms.push_back(&room);
			}
		}
		return dustyRooms;
	}

	//récupère les pièces avec des bijoux
	std::vector<Room*> Captor::getRoomsWithJewel()
	{
		std::vector<Room*> roomsWithJewel;
		for (auto& room : this->_agent->beliefs.m_manor->getRooms())
		{
			if (room.getJewel() == true)
			{
				roomsWithJewel.push_back(&room);
			}
		}
		return roomsWithJewel;
	}

	//récupère la mesure de performance depuis l'environnement 
	int Captor::getPerformanceMesure()
	{
		return this->_agent->environment->getScore();
	}
