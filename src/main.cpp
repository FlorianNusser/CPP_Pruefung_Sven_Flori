#include "game.hpp"
#include "gui.hpp"
#include "player.hpp"
#include "menu.hpp"
#include "gamemode.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>

int main()
{
    //Menü
    Menu menu;
    Player player = menu.namePlayer();

    player.printProperties();

    Playmode gamemode = menu.selectGamemode();
    std::string cascadeFilePath = Constants::CASCADE_FILE_PATH;
    Game game(cascadeFilePath, gamemode, player);

    game.startGame();
    game.run();


    return 0;
}
