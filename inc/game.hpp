#ifndef GAME_HPP
#define GAME_HPP

#include "dodgeTheBalls.hpp"
#include "gamemode.hpp"
#include "gui.hpp"

#include <opencv2/opencv.hpp>
#include <string>

//class Gui;

class Game
{
public:
    Game(const std::string& cascadePath, Playmode playmode);
    ~Game();
    bool initialize();
    void startGame();
    void run();
    
private:
    cv::VideoCapture cap;
    cv::CascadeClassifier faceCascade;
    const std::string windowName = "Face Detection";
    int frameWidth;
    int frameHeight;
    //neu
    Playmode m_playmode;
    Gui m_gui;
    DodgeTheBalls m_dodgeTheBalls;
};

#endif // GAME_HPP
