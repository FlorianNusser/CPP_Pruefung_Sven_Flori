#ifndef GAME_HPP
#define GAME_HPP

#include "dodgeTheBalls.hpp"
#include "catchTheSquares.hpp"
#include "gamemode.hpp"
#include "gui.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>

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
    Playmode m_playmode;
    DodgeTheBalls m_dodgeTheBalls;
    CatchTheSquares m_catchTheSquares;  // Sicherstellen, dass dies deklariert ist
    Gui m_gui;
    cv::CascadeClassifier faceCascade;
    cv::VideoCapture cap;
    int frameWidth;
    int frameHeight;
    const std::string windowName = "Face Detection Game";
    int m_score = 0;
};

#endif // GAME_HPP
