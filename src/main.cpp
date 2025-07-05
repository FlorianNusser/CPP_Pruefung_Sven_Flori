#include "game.hpp"
#include "gui.hpp"
#include "player.hpp"
#include "menu.hpp"
#include "gamemode.hpp"

#include <iostream>
#include <string>

int main()
{
//Menü
    Menu menu;
    Player player = menu.namePlayer();

    player.printProperties();

    Gamemode gamemode = menu.selectGamemode();

    menu.startGame();
    //Gui gui(Color::Black, player.m_name, Playmode::DodgeTheBalls); // Standardwert für Playmode

    return 0;
}
