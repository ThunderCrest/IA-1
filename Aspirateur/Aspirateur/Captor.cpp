#include "Captor.h"
#include "Agent.h"

	Captor::Captor(Agent &agent)
	{
		this->_agent = &agent;
	}

	int Captor::getCurrentRoomIndex()
	{
		int index = 0;
		
		if (this->_agent)
		{
			for (auto& room : this->_agent->m_manor->getRooms())
			{
				if (room.getAgent() == true)
				{
					return index;
				}
				index++;
			}
			return -1;
		}
		else {
			return -1;
		}
		
		return this->_agent->m_manor->getSizeY() ;
	}

	int Captor::getPerformanceMesure()
	{
		//see with Mona Le Coz 
		return 0;
	}
