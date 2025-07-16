#ifndef GUI_HPP
#define GUI_HPP

#include <opencv2/opencv.hpp>
#include <string>
//#include "game.hpp"
#include "player.hpp"
#include "gamemode.hpp"
#include "color.hpp"
#include "dodgeTheBalls.hpp"

class Game; //Vorwärtsdeklaration

class Gui
{
public:
    Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode);
    virtual ~Gui();


    bool initialize();
    void display();

    std::vector<cv::Rect> updateFrame(cv::Mat& frame);

    int getKeyboard();

    void showScore(cv::Mat& frame, int score);
    void showGameOver(cv::Mat &frame, int score, Player player);

private:
    cv::CascadeClassifier faceCascade;
    int m_frameWidth;
    int m_frameHeight;
    Color m_textcolor;
    //brauchen wir das?
    Playmode m_playmode;
    Game &m_game;
};


#endif //GUI_HPP