#ifndef MENU_HPP
#define MENU_HPP

#include "player.hpp"
#include "gamemode.hpp"

#include <iostream>
#include <string>

class Menu
{
public:
    Player namePlayer();
    Gamemode selectGamemode();
    void startGame();


private:

};


#endif //MENU_HPP