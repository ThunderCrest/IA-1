#pragma once
#include "Captor.h"
class PerformanceValueCaptor : public Captor
{
	virtual void* ObserveEnvironment() override;
};

