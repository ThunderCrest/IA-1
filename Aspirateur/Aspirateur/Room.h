#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Room
{
public:
	Room(int x, int y);
	~Room();

	//Accesseur

	int getX() const;
	int getY() const;
	bool getJewel() const;
	bool getDirt() const;
	bool getAgent() const;

	//Controller

	void setJewel(bool isPresent);
	void setDirt(bool isPresent);
	void setAgent(bool isPresent);

	// autre fonction
	void Vacuum();
	void PickupJewel();

	void initRoom();

private:
	int m_x;
	int m_y;
	bool m_agent;
	bool m_jewel;
	bool m_dirt;

};

inline bool operator==(const Room& lhs, const Room& rhs)
{
	if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getDirt() == rhs.getDirt() && lhs.getJewel() == rhs.getJewel())
		return true;
	return false;
}

inline std::ostream& operator<<(std::ostream& out, Room& r)
{
	out << "P : " << r.getDirt() << ", B : " << r.getJewel();
	if (r.getAgent())
		out << " Agent ";
	return out;
}

