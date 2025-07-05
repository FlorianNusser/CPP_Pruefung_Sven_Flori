#include "player.hpp"
#include <iostream>

int Player::idSetter = 0;

Player::Player(std::string &name): m_name(name), m_id(idSetter)
{
    idSetter++;
}

Player::~Player()
{
}


int Player::getId() const
{
    return m_id;
}

void Player::printProperties()
{

    std::cout << "Playername: " << m_name << std::endl;
    std::cout << "Player ID: " << m_id << std::endl;
    std::cout << "-------------" << std::endl;
}