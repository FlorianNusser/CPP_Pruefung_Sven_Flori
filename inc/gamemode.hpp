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
    Gamemode(Playmode &playmode);
    virtual ~Gamemode();

    void calcScore();

    int getScore() const;
    int getTime() const ;
    Playmode getPlaymode() const;
    void setScore(int score);
    void setTime(int time);

private:
    Playmode m_playmode;
    int m_score;
    int m_time;
};

#endif // GAMEMODE_HPP