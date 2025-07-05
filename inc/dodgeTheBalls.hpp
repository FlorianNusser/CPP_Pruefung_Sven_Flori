#ifndef DODGE_THE_BALLS_HPP
#define DODGE_THE_BALLS_HPP


#include <opencv2/opencv.hpp>
#include <vector>

// Struktur für einen Ball
struct Ball {
    cv::Point2f position;
    float radius;
    cv::Scalar color;
    float velocityY;
};

class DodgeTheBalls {
public:
    DodgeTheBalls(int width, int height);

    void spawnBall();
    void updateBalls();
    void drawBalls(cv::Mat& frame) const;
    bool checkCollision(const cv::Rect& playerRect) const;
    void removeOffscreenBalls();

    // Zugriff auf aktuelle Bälle (z.B. für Tests)
    const std::vector<Ball>& getBalls() const;

private:
    int m_width;
    int m_height;
    std::vector<Ball> m_balls;
};


#endif // DODGE_THE_BALLS_HPP