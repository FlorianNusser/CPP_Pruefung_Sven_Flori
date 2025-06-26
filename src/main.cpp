#include "game.hpp"
#include <string>

int main() {
//Menü
    std::string name;
    
    
    std::cout << "-------------" << std::endl;
    std::cout << "Spielernamen eingeben: ";
    std::cin >> name;
    std::cout << "\n";
    
    
//Start des Spiels    
    std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}
