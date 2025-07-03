#include "dodgeTheBalls.hpp"
#include <random>

DodgeTheBalls::DodgeTheBalls(int width, int height)
    : m_width(width), m_height(height) {}

void DodgeTheBalls::spawnBall() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(20.0f, m_width - 20.0f);
    std::uniform_real_distribution<float> rDist(15.0f, 30.0f);
    std::uniform_real_distribution<float> vDist(3.0f, 7.0f);

    Ball ball;
    ball.position = cv::Point2f(xDist(gen), 0.0f);
    ball.radius = rDist(gen);
    ball.color = cv::Scalar(0, 0, 255); // Rot
    ball.velocityY = vDist(gen);

    m_balls.push_back(ball);
}

void DodgeTheBalls::updateBalls() {
    for (auto& ball : m_balls) {
        ball.position.y += ball.velocityY;
    }
}

void DodgeTheBalls::drawBalls(cv::Mat& frame) const {
    for (const auto& ball : m_balls) {
        cv::circle(frame, ball.position, static_cast<int>(ball.radius), ball.color, -1);
    }
}

bool DodgeTheBalls::checkCollision(const cv::Rect& playerRect) const {
    for (const auto& ball : m_balls) {
        cv::Point2f center = ball.position;
        float radius = ball.radius;
        // Prüfe, ob der Mittelpunkt des Balls im Spielerrechteck liegt
        if ((center.x > playerRect.x && center.x < playerRect.x + playerRect.width) &&
            (center.y > playerRect.y && center.y < playerRect.y + playerRect.height)) {
            return true;
        }
        // Optional: genauere Kollisionserkennung (Kreis-Rechteck)
    }
    return false;
}

void DodgeTheBalls::removeOffscreenBalls() {
    m_balls.erase(
        std::remove_if(m_balls.begin(), m_balls.end(),
            [this](const Ball& ball) { return ball.position.y - ball.radius > m_height; }),
        m_balls.end());
}

const std::vector<Ball>& DodgeTheBalls::getBalls() const {
    return m_balls;
}