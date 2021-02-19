#pragma once
#include "Manor.h"
#include <vector>
#include "Agent.h"

class Environment
{
public:
	Environment(Agent* agent, Manor* manor);
	~Environment();

	Manor& getManor();

	bool gameIsRunning() const;
	bool shouldThereBeANewDirtySpace() const;
	bool shouldThereBeANewLostJewel() const;

	void run();
	void killEnvironment() { m_bAlive = false; }

	void increaseScore(int a = 1);
	void decreaseScore(int a = 1);
	int getScore();

	//performanceMesure -> le score augmente en fonction du nombre de pièces poussièreuses, de sa consommation d'énergie, du nombre de bijoux avalé.



private:

	Manor* m_manor;
	Agent* m_agent;
	bool m_bAlive;
	bool m_gameIsRunning;
	time_t m_lastTickTime;
	time_t m_currentTickTime;
	int m_score;

	

};

