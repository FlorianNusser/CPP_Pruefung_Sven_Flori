#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>

class Player
{
public:
    Player(std::string name);
    virtual ~Player();
    static int getId();
protected:

private:
    std::string m_name;
    static int m_id;
};


#endif