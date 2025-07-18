#include "player.hpp"
#include "constants.hpp"
#include <iostream>
#include <fstream>
#include <string>

Player::Player(const std::string &name): m_name(name)
{
    int idSetter = 0;;
    //read playerID data
    std::ifstream in(Constants::PLAYER_ID);
    std::string idStr;
    if (in >> idStr) {
        try {
            idSetter = std::stoi(idStr);
        } catch (const std::invalid_argument&) {
            std::cerr << "Fehler: ungültiger Wert in PLAYER_ID.txt\n";
            idSetter = 0;
        } catch (const std::out_of_range&) {
            std::cerr << "Fehler: Zahl in PLAYER_ID.txt außerhalb des gültigen Bereichs\n";
            idSetter = 0;
        }
    }
    else
    {
        std::cerr << "Fehler beim Einlesen der ID!" << std::endl;
    }
    
    idSetter ++;
    m_id = idSetter;
    //write new playerID in data
    std::ofstream out(Constants::PLAYER_ID, std::ios::trunc);
    if(!out)
    {
        std::cerr << "Error when trying to write in " << Constants::PLAYER_ID << std::endl;
    }
    out << idSetter;
}

Player::~Player()
{
}


int Player::getId() const
{
    return m_id;
}

std::string Player::getPlayername()
{
    return m_name;
}

void Player::printProperties()
{

    std::cout << "Playername: " << m_name << std::endl;
    std::cout << "Player ID: " << m_id << std::endl;
    std::cout << "-------------" << std::endl;
}