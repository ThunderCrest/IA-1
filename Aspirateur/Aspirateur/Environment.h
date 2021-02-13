#pragma once
#include "Manor.h"
#include <vector>


class Environment
{
public:
	Environment();
	~Environment();

	Manor& getManor();

	bool gameIsRunning() const;
	bool shouldThereBeANewDirtySpace() const;
	bool shouldThereBeANewLostJewel() const;

	void Run();
	void KillEnvironment() { m_bAlive = false; }
	//performanceMesure -> le score augmente en fonction du nombre de pièces poussièreuses, de sa consommation d'énergie, du nombre de bijoux avalé.

private:

	Manor m_manor;
	bool m_bAlive;
	bool m_gameIsRunning;
	time_t m_lastTickTime;
	time_t m_currentTickTime;

};

