#ifndef GUI_HPP
#define GUI_HPP

#include <opencv2/opencv.hpp>
#include <string>
//#include "game.hpp"
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
    //Lucas Vorschläge //noch implementieren
    std::vector<cv::Rect> updateFrame(cv::Mat& frame);
    //void drawBalls(cv::Mat& frame, const std::vector<std::unique_ptr<Ball>>& balls);
    int getKeyboard();

private:
    cv::CascadeClassifier faceCascade;
    const std::string m_windowName = "Face Detection";
    int m_frameWidth;
    int m_frameHeight;
    int m_score;
    Color m_textcolor;
    //const std::string m_playername;
    Playmode m_playmode;
    Game &m_game;
};


#endif //GUI_HPP