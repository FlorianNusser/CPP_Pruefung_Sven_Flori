#ifndef GUI_HPP
#define GUI_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include "game.hpp"

enum class Color{
    White,
    Black,
    Red,
    Green,
    Blue,
    Purple
};

enum class Playmode{
DodgeTheBalls,
CatchTheSquares
};


class Gui
{
public:
    Gui(Color textcolor, const std::string& playername, Playmode playmode);
    virtual ~Gui();




private:
    int m_frameWidth;
    int m_frameHeight;
    int m_score;
    Color m_textcolor;
    const std::string m_playername;
    Playmode m_playmode;
};


#endif