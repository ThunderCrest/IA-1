#include "Manor.h"
#include "Effector.h"


Manor::Manor(int width, int height)
{
	// Création d'un manoir rempli de pièces (matrice width*height)
	m_sizeX = width;
	m_sizeY = height;

	for (int i = 0; i < m_sizeX; ++i)
	{
		for (int j = 0; j < m_sizeY; ++j)
		{
			Room room(j, i);
			room.initRoom();
			m_rooms.push_back(room);
		}
	}

}

Manor::~Manor()
{

}

int Manor::getSizeX()
{
	return m_sizeX;
}

int Manor::getSizeY()
{
	return m_sizeY;
}

// Retourne toutes les pièces dans un vecteur de pièces
std::vector<Room>& Manor::getRooms()
{
	return m_rooms;
}

// retourne une pièce demandée
Room& Manor::getRoom(int position)
{
	if (position < m_rooms.size())
	{
		return m_rooms.at(position);
	}
	throw std::logic_error("position trop grande");
}

// retourne la pièce se trouvant à coté de la pièce courante en fonction de la direction donnée
Room* Manor::getRoomInDirection(Room* currentRoom, actions direction)
{
	Room* room;
	switch (direction)
	{
	case actions::goLeft:
		if(currentRoom->getX() > 0)
		{
			return &getRoom(5 * currentRoom->getY() + currentRoom->getX() - 1);
		}
		return nullptr;
	case actions::goRight:
		if (currentRoom->getX() < 4)
		{
			return &getRoom(5 * currentRoom->getY() + currentRoom->getX() + 1);
		}
		return nullptr;
	case actions::goTop:
		if (currentRoom->getY() > 0)
		{
			return &getRoom(5 * currentRoom->getY() + currentRoom->getX() - 5);
		}
		return nullptr;
	case actions::goBottom:
		if (currentRoom->getY() < 4)
		{
			return &getRoom(5 * currentRoom->getY() + currentRoom->getX() + 5);
		}
		return nullptr;
	default:
		return nullptr;
	}
}

// Retourne l'index correspondant à la pièce donnée
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

// Retourne toutes les pièces qui ne sont pas vide
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