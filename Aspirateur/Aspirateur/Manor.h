#pragma once

#include <iostream>
#include <vector>
#include "Room.h"


class Manor
{
public:
	Manor(int width, int height);

	int getSizeX();
	int getSizeY();

	std::vector<Room>& getRooms();
	Room& getRoom(int position);
	int findIndex(Room& currentRoom) const;
	std::vector<Room*> getNotEmptyRoom();
	int getIndexRoom(Room room);

private:
	int m_sizeX;
	int m_sizeY;
	std::vector<Room> m_rooms;
};