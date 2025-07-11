#include "gamemode.hpp"

Gamemode::Gamemode(Playmode& playmode): m_playmode(playmode), m_score(0), m_time(0)
{}

Gamemode::~Gamemode()
{}


void Gamemode::calcScore()
{

}



int Gamemode::getScore() const
{
    return m_score;
}
int Gamemode::getTime() const
{
    return m_time;
}
Playmode Gamemode::getPlaymode() const
{
    return m_playmode;
}
void Gamemode::setScore(int score)
{
    m_score = score;
}
void Gamemode::setTime(int time)
{
    m_time = time;
}