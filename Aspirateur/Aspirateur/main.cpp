// AgentAspirateur.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
//

#include <iostream>
#include "Room.h"
#include "Environment.h"
#include "Agent.h"
#include <vector>
#include <thread>

int main()
{


    Manor* manor = new Manor(5,5);
    Agent* agent = new Agent(manor);
    Environment* environment = new Environment(agent, manor);


    std::thread environmentThread(&Environment::Run, environment);
    std::thread agentThread(&Agent::Run, agent);

    std::string input;
    std::cin >> input;

    while(input != "0")
    {
        if (input == "1") 
        {
            agent->SwitchExplorationMethod();
        }
        std::cin >> input;
    }

    environment->KillEnvironment();
    agent->KillAgent();

    if (environmentThread.joinable())environmentThread.join();
    if (agentThread.joinable())agentThread.join();

    delete manor;
    delete agent;
}

// Ex�cuter le programme�: Ctrl+F5 ou menu D�boguer�> Ex�cuter sans d�bogage
// D�boguer le programme�: F5 ou menu D�boguer�> D�marrer le d�bogage

// Astuces pour bien d�marrer�: 
//   1. Utilisez la fen�tre Explorateur de solutions pour ajouter des fichiers et les g�rer.
//   2. Utilisez la fen�tre Team Explorer pour vous connecter au contr�le de code source.
//   3. Utilisez la fen�tre Sortie pour voir la sortie de la g�n�ration et d'autres messages.
//   4. Utilisez la fen�tre Liste d'erreurs pour voir les erreurs.
//   5. Acc�dez � Projet�> Ajouter un nouvel �l�ment pour cr�er des fichiers de code, ou � Projet�> Ajouter un �l�ment existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, acc�dez � Fichier�> Ouvrir�> Projet et s�lectionnez le fichier .sln.
