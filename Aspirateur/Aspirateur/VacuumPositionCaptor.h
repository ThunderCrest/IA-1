#pragma once
#include "Captor.h"
class VacuumPositionCaptor : public Captor
{
    virtual void* ObserveEnvironment() override;
};

