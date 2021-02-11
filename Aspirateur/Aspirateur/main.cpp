// AgentAspirateur.cpp : Ce fichier contient la fonction 'main'. L'ex�cution du programme commence et se termine � cet endroit.
//

#include <iostream>
#include "Room.h"
#include "Manor.h"
#include "Agent.h"
#include <vector>
#include <thread>

int main()
{
    bool isDirty = false;
    bool isJewel = false;
    Room room(1, 1);

    // test Room

    //for (int i = 0; i < 20; i++)
    //{
    //    room.setDirt(false);
    //    room.setJewel(false);

    //    room.initRoom();
    //    isDirty = room.getDirt();
    //    isJewel = room.getJewel();

    //    std::cout << "la piece est sale ? " << isDirty << "\n";
    //    std::cout << "Y a t-il un bijou ? " << isJewel << "\n\n";
    //}

    // test Manor

    Manor* manor = new Manor(5, 5);
    std::cout << manor << "\n";
    std::vector<Room> rooms = manor->getRooms();
    //for (int n = 0; n < manor.getRooms().size(); ++n)
    //{
    //    Room room = manor.getRoom(n);
    //    std::cout << "piece : " << room.getX() << "," << room.getY() << "\n";
    //    std::cout << "sale : " << room.getDirt() << " et bijou : " << room.getJewel() << "\n\n";
    //}

    Agent* agent = new Agent(manor);

    std::thread manorThread(&Manor::Run, manor);
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

    manor->KillManor();
    agent->KillAgent();

    if (manorThread.joinable())manorThread.join();
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
