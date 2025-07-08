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
    std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath, gamemode.getPlaymode());

    game.startGame();
    game.run();


    return 0;
}
