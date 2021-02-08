#include "JewelPickupEffector.h"

void JewelPickupEffector::ExecuteEffector(Room* room)
{
	room->PickupJewel();
}
