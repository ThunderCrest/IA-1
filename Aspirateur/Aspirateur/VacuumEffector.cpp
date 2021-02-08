#include "VacuumEffector.h"

void VacuumEffector::ExecuteEffector(Room* room)
{
	room->Vacuum();
}
