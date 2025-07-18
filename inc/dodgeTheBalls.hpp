#ifndef DODGE_THE_BALLS_HPP
#define DODGE_THE_BALLS_HPP


#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <ball.hpp>
#include "gamemode.hpp"


class DodgeTheBalls {
public:

    DodgeTheBalls(int width, int height, Playmode playmode, bool useRandomColors = true);
    virtual ~DodgeTheBalls();

    void spawnBall();
    void updateBalls();
    void drawBalls(cv::Mat& frame) const;
    bool checkCollision(const cv::Rect& playerRect) const;
    void removeOffscreenBalls();
    void calcScore(int &score);

   // Access to current balls (e.g. for tests)
    const std::vector<std::shared_ptr<Ball>>& getBalls() const;

    void removeCollidedBalls(const cv::Rect& playerRect);

private:
    std::vector<std::shared_ptr<Ball>> m_balls;
    int m_screenWidth;
    int m_screenHeight;
    Color getRandomColor();
    Playmode m_playmode;
    bool m_useRandomColors;
};


#endif // DODGE_THE_BALLS_HPP