#pragma once
#include "Captor.h"
class JewelCaptor : public Captor
{
	virtual void* ObserveEnvironment(/*Environment pointer*/) override;
};

