#pragma once
#include "Manor.h"


class Environment
{
public:
	Environment();
	~Environment();

	Manor& getManor();

	bool gameIsRunning() const;
	bool shouldThereBeANewDirtySpace() const;
	bool shouldThereBeANewLostJewel() const;


private:

	Manor m_manor;
	bool m_gameIsRunning;

};

