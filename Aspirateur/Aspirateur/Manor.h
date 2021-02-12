#pragma once

#include <iostream>
#include <vector>
#include "Room.h"


class Manor
{
public:
	Manor(int width, int height);
	~Manor();

	int getSizeX();
	int getSizeY();

	std::vector<Room>& getRooms();
	Room& getRoom(int position);
	int findIndex(Room& currentRoom) const;
	std::vector<Room*> getNotEmptyRoom();



private:

	int m_sizeX;
	int m_sizeY;
	std::vector<Room> m_rooms;
};


inline std::ostream& operator<<(std::ostream& out, Manor& m)
{
	int position = 0;
	for (int positionX = 0; positionX < m.getSizeX(); ++positionX) {
		out << " | ";
		for (int positionY = 0; positionY < m.getSizeY(); ++positionY) {
			out << m.getRoom(position) << " | ";
			++position;
		}
		out << "\n\n";
	}
	return out;
}