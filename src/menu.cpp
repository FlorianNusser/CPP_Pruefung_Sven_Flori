#include "menu.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "gamemode.hpp"

#include <limits>


Player Menu::namePlayer()
    {
        std::string name;
        std::cout << "-------------" << std::endl;
        std::cout << "Enter Playername: ";
        std::getline(std::cin, name);
        std::cout << "-------------" << std::endl;
        return Player(name);
    }

Playmode Menu::selectGamemode()
    {
        Playmode playmode;
        int choice = 0;
        bool validchoice = false;
        // Validation of input
        while(validchoice == false)
        {
            std::cout << "1. Dodge the Balls" << std::endl;
            std::cout << "2. Catch the Squares" << std::endl;
            std::cout << "Enter Gamemode (1,2): ";
            std::cout << "Please select a valid option (1 or 2): ";
            std::cin >> choice;

        if(std::cin.fail()) {
        std::cin.clear(); // Fehlerstatus löschen
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Rest der Zeile ignorieren
        std::cout << "Put in a valid number!\n";
        continue; // Schleife neu starten
}

        switch (choice)
        {
            case 1:
                playmode = Playmode::DodgeTheBalls;
                validchoice = true;
                break;
            case 2:
                playmode = Playmode::CatchTheSquares;
                validchoice = true;
                break;
            default:
                std::cout << "Invalid choice!\n" << "Please Select a valid option!" << std::endl;
                break;
        }

        }
        return Playmode(playmode);
    }

