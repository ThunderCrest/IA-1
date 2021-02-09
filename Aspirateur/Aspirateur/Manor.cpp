#include "Manor.h"


Manor::Manor(int width, int height)
{
	m_sizeX = width;
	m_sizeY = height;

	for (int i = 0; i < m_sizeX; ++i)
	{
		for (int j = 0; j < m_sizeY; ++j)
		{
			Room room(i, j);
			room.initRoom();
			m_rooms.push_back(room);
		}
	}

}

int Manor::getSizeX()
{
	return m_sizeX;
}

int Manor::getSizeY()
{
	return m_sizeY;
}

std::vector<Room>& Manor::getRooms()
{
	return m_rooms;
}

Room& Manor::getRoom(int position)
{
	if (position < m_rooms.size())
	{
		return m_rooms.at(position);
	}
	throw std::logic_error("position trop grande");
}

int Manor::findIndex(Room& currentRoom) const
{
	for (int i = 0; i < m_rooms.size(); ++i)
	{
		if (m_rooms[i] == currentRoom)
		{
			return i;
		}
	}
	return -1;
}

std::vector<Room*> Manor::getNotEmptyRoom()
{
	std::vector<Room*> notEmptyRoom;
	for (Room& currentRoom : m_rooms)
	{
		if (currentRoom.getDirt() || currentRoom.getJewel())
		{
			notEmptyRoom.push_back(&currentRoom);
		}
	}
	return notEmptyRoom;
}

void Manor::Run()
{
	while(true)
	{

	}
}

