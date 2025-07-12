#ifndef GAME_HPP
#define GAME_HPP

#include "dodgeTheBalls.hpp"
#include "catchTheSquares.hpp"
#include "gamemode.hpp"
#include "gui.hpp"
#include "player.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <vector>
#include <gameModeInterface.hpp>

//class Gui;

class Game
{
public:
    Game(const std::string& cascadePath, Playmode playmode, Player m_player);
    ~Game();
    bool initialize();
    void startGame();
    void run();

private:
    std::unique_ptr<GameModeInterface> m_gameMode;
    Playmode m_playmode;
    DodgeTheBalls m_dodgeTheBalls;
    CatchTheSquares m_catchTheSquares;  // Sicherstellen, dass dies deklariert ist
    Gui m_gui;
    Player m_player;
    cv::CascadeClassifier faceCascade;
    cv::VideoCapture cap;
    int frameWidth;
    int frameHeight;
    int m_score = 0;
};

#endif // GAME_HPP
