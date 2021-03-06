﻿#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <windows.h>
#include <wincon.h>


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

	void initRoom();

private:
	int m_x;
	int m_y;
	bool m_agent;
	bool m_jewel;
	bool m_dirt;

};

// Ajout d'un op�rateur pour pouvoir verifier si deux rooms sont identiques
inline bool operator==(const Room& lhs, const Room& rhs)
{
	if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getDirt() == rhs.getDirt() && lhs.getJewel() == rhs.getJewel())
	{
		return true;
	}
	return false;
}


// Ajout d'un op�rateur pour pouvoir afficher les poussieres, les bijoux et l'agent dans une pi�ce, et gere les couleurs
inline std::ostream& operator<<(std::ostream& out, Room& r)
{
	if (r.getDirt())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		out << " P ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else 
	{
		out << "   ";
	}
	if (r.getJewel())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		out << " B ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else
	{
		out << "   ";
	}
	if (r.getAgent())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		out << " A ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	}
	else
	{
		out << "   ";
	}
	return out;
}

