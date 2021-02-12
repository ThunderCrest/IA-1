#include "Agent.h"
#include "Manor.h"
#include <cstdlib>

Agent::Agent(Manor* manor)
{
	this->m_manor = manor;
	m_bAlive = true;
	m_bUsingInformedMethod = true;
}

void Agent::Run()
{
	this->m_lastTickTime = -1;
	while(m_bAlive)
	{
		time(&this->m_currentTickTime);
		if(this->m_currentTickTime - this->m_lastTickTime > 0)
		{
			this->m_lastTickTime = this->m_currentTickTime;
			//std::cout << m_lastTickTime << std::endl;
		    
		    if(this->m_currentIterationsToExploration >= this->m_iterationsToExploration)
			{
				this->m_currentIterationsToExploration = 0;
				//Observe
				//Explore
			}



			this->m_currentIterationsToExploration++;
		}
	}
}

void Agent::SwitchExplorationMethod()
{
	m_bUsingInformedMethod = !m_bUsingInformedMethod;
	if(m_bUsingInformedMethod)
	{
		std::cout << "Using Informed" << std::endl;
	}
	else
	{
		std::cout << "Using Uninformed" << std::endl;
	}
}
