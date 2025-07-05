#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>

class Player
{
public:
    Player(std::string &name);
    virtual ~Player();
    int getId() const;

    void printProperties();
protected:

private:
    std::string m_name;
    int m_id;
    static int idSetter;
};


#endif