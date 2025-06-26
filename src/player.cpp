#include "player.hpp"
#include <iostream>

int Player::m_id = 0;

Player::Player(std::string name): m_name(name)
{
    m_id++;
}

int Player::getId()
{
    return m_id;
}