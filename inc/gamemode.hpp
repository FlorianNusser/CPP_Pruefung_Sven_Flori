#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

enum class Playmode
{
    CatchTheSquares,
    DodgeTheBalls
};


class Gamemode
{
public:
    Gamemode(Playmode& playmode);

    virtual ~Gamemode();

    Playmode getGametype() const { return m_playmode; }
    int getScore() const { return m_score; }
    int getTime() const { return m_time; }
    Playmode getPlaymode() const { return m_playmode; }

    void setScore(int score) { m_score = score; }
    void setTime(int time) { m_time = time; }


private:
    Playmode m_playmode;
    int m_score;
    int m_time;
    //int m_lives;
    //int m_level;
    //int m_speed;
};


#endif //GAMEMODE_HPP