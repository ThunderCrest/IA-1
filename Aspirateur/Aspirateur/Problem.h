#pragma once

class Room;
class Manor;
enum class goals;

struct Problem
{
	Room* startingRoom;
	Room* targetRoom;
	Manor* manor;
	goals goal;
};

