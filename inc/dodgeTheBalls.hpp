#ifndef DODGE_THE_BALLS_HPP
#define DODGE_THE_BALLS_HPP


#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <ball.hpp>
#include <drawBall.hpp>



class DodgeTheBalls {
public:

    DodgeTheBalls(int width, int height);
    virtual ~DodgeTheBalls();

    void spawnBall();
    void updateBalls();
    //wird durch drawBall Klasse ersetzt
    void drawBalls(cv::Mat& frame) const;
    bool checkCollision(const cv::Rect& playerRect) const;
    void removeOffscreenBalls();
    void calcScore(int &score);

    // Zugriff auf aktuelle Bälle (z.B. für Tests)
    const std::vector<std::shared_ptr<Ball>>& getBalls() const;

    void removeCollidedBalls(const cv::Rect& playerRect);

private:
    std::vector<std::shared_ptr<Ball>> m_balls;
    int m_screenWidth;
    int m_screenHeight;
};


#endif // DODGE_THE_BALLS_HPP