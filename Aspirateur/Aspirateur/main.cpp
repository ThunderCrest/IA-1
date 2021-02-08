// AgentAspirateur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Room.h"
#include "Manor.h"
#include <vector>

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

    Manor manor(5, 5);
    std::vector<Room> rooms = manor.getRooms();
    for (int n = 0; n < manor.getRooms().size(); ++n)
    {
        Room room = manor.getRoom(n);
        std::cout << "piece : " << room.getX() << "," << room.getY() << "\n";
        std::cout << "sale : " << room.getDirt() << " et bijou : " << room.getJewel() << "\n\n";
    }

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
