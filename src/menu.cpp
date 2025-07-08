#include "menu.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "gamemode.hpp"


Player Menu::namePlayer()
    {
        std::string name;
        std::cout << "-------------" << std::endl;
        std::cout << "Enter Playername: ";
        std::cin >> name;
        std::cout << "-------------" << std::endl;
        return Player(name);
    }

Gamemode Menu::selectGamemode()
    {
        Playmode playmode;
        std::cout << "1. Dodge the Balls" << std::endl;
        std::cout << "2. Catch the Squares" << std::endl;
        std::cout << "Enter Gamemode (1,2): ";

        int choice;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
                playmode = Playmode::DodgeTheBalls;
                break;
            case 2:
                playmode = Playmode::CatchTheSquares;
                break;
            default:
                std::cout << "Not an Option. Selected 'Dodge the Balls' by default." << std::endl;
                playmode = Playmode::DodgeTheBalls;
                break;
        }
        return Gamemode(playmode);

    }

