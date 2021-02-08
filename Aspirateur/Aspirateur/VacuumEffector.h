#pragma once
#include "Effector.h"

class VacuumEffector : public Effector
{
	virtual void ExecuteEffector(Room* room) override;
};

