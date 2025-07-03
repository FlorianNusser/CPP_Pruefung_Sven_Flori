#include "game.hpp"
#include "gui.hpp"

#include <iostream>
#include <string>

int main() {
//Menü
    std::string name;


    std::cout << "-------------" << std::endl;
    std::cout << "Spielernamen eingeben: ";
    std::cin >> name;
    std::cout << "\n";

    std::cout << "Spielmodus auswählen:" << std::endl;
    std::cout << "1. Dodge the Balls" << std::endl;
    std::cout << "2. Catch the Squares" << std::endl;
    
    
    int choice;
    std::cin >> choice;
    Playmode playmode;
    switch (choice) {
        case 1:
            playmode = Playmode::DodgeTheBalls;
            break;
        case 2:
            playmode = Playmode::CatchTheSquares;
            break;
        default:
            std::cout << "Ungültige Auswahl. Standardmäßig wird 'Dodge the Balls' ausgewählt." << std::endl;
            playmode = Playmode::DodgeTheBalls;
            break;
    }
    Gui gui(Color::Black, name, Playmode::DodgeTheBalls); // Standardwert für Playmode

    std::cout << "Spielername: " << name << std::endl;
    std::cout << "Spielmodus: " << (playmode == Playmode::DodgeTheBalls ? "Dodge the Balls" : "Catch the Squares") << std::endl;
    std::cout << "Textfarbe: Weiß" << std::endl;
    std::cout << "Press Enter to start the game..." << std::endl;
    std::cin.ignore(); // Überspringt das vorherige Eingabezeichen
    std::cin.get(); // Warten auf Enter-Taste
    std::cout << "\n";



//Start des Spiels
    std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}
