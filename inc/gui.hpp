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
    //void renderFrame(cv::Mat& frame, const DodgeTheBalls& model, const cv::Rect& playerRect);
    void display();
    //Lucas Vorschläge //noch implementieren
    std::vector<cv::Rect> updateFrame(cv::Mat& frame);
    void drawBalls(cv::Mat& frame, std::vector<Ball> balls);
    int getKeybord();






private:
    //cv::VideoCapture cap;
    cv::CascadeClassifier faceCascade;
    const std::string m_windowName = "Face Detection";
    int m_frameWidth;
    int m_frameHeight;
    int m_score;
    Color m_textcolor;
    //Playername wird von Klasse Player geliefert
    //const std::string m_playername;
    Playmode m_playmode;
    Game &m_game;
};


#endif //GUI_HPP