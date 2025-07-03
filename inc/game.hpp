#ifndef GAME_HPP
#define GAME_HPP

#include "dodgeTheBalls.hpp"

#include <opencv2/opencv.hpp>
#include <string>

class Game
{
public:
    Game(const std::string& cascadePath);
    ~Game();
    bool initialize();
    void run();
private:
    cv::VideoCapture cap;
    cv::CascadeClassifier faceCascade;
    const std::string windowName = "Face Detection";
    int frameWidth;
    int frameHeight;
    //neu
    DodgeTheBalls m_dodgeTheBalls;
};

#endif // GAME_H
