#include "Captor.h"
#include "Agent.h"
#include "Environment.h"
	Captor::Captor(Agent &agent)
	{
		this->_agent = &agent;
	}

	int Captor::getCurrentRoomIndex()
	{
		int index = 0;

			for (auto& room : this->_agent->beliefs.m_manor->getRooms())
			{
				if (room.getAgent() == true)
				{
					this->_agent->beliefs.currentRoom = &room;
					return index;
				}
				index++;
			}
		return -1 ;
	}

	std::vector<Room> Captor::getDustyRooms()
	{
		std::vector<Room> dustyRooms;
		for (auto& room : this->_agent->beliefs.m_manor->getRooms())
		{
			if (room.getDirt() == true)
			{
				dustyRooms.push_back(room);
			}
		}
		this->_agent->beliefs.dustyRooms = dustyRooms;
		return dustyRooms;
	}

	std::vector<Room> Captor::getRoomsWithJewel()
	{
		std::vector<Room> roomsWithJewel;
		for (auto& room : this->_agent->beliefs.m_manor->getRooms())
		{
			if (room.getJewel() == true)
			{
				roomsWithJewel.push_back(room);
			}
		}
		this->_agent->beliefs.roomsWithJewel = roomsWithJewel;
		return roomsWithJewel;
	}

	int Captor::getPerformanceMesure()
	{
		return this->_agent->environment->getScore();
	}
