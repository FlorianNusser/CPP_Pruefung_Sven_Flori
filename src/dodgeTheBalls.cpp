#include "dodgeTheBalls.hpp"
#include "ball.hpp"
#include "randomGenerator.hpp"
#include "constants.hpp"
#include <algorithm>

DodgeTheBalls::DodgeTheBalls(int width, int height, Playmode playmode, bool useRandomColors)
    : m_screenWidth(width), m_screenHeight(height), m_playmode(playmode)
{}

DodgeTheBalls::~DodgeTheBalls()
{}

Color DodgeTheBalls::getRandomColor() 
{
    if(m_useRandomColors)
    {
        std::uniform_int_distribution<int> colorDist(2, 4); // Enum-Values for blue, red and green
        return static_cast<Color>(colorDist(RandomGenerator::getGenerator()));
    }
    return DodgeTheBallsConfig::BALL_COLOR; // Standardfarbe für andere Modi

}

void DodgeTheBalls::spawnBall() {
    std::uniform_int_distribution<int> radiusDist(DodgeTheBallsConfig::MIN_RADIUS,DodgeTheBallsConfig::MAX_RADIUS);
    std::uniform_int_distribution<int> velocityDist(DodgeTheBallsConfig::MIN_VELOCITY, DodgeTheBallsConfig::MAX_VELOCITY);
    std::uniform_int_distribution<int> xSpawnDist(DodgeTheBallsConfig::X_SPAWN_BORDER, m_screenWidth - DodgeTheBallsConfig::X_SPAWN_BORDER);

    int velocityY = velocityDist(RandomGenerator::getGenerator());
    int radius = radiusDist(RandomGenerator::getGenerator());
    const cv::Point2f position = cv::Point2f(xSpawnDist(RandomGenerator::getGenerator()), 0);

    Color randomColor = getRandomColor();
    auto ball = std::make_shared<Ball>(position, randomColor, velocityY, radius);

   

    m_balls.push_back(ball);
}

void DodgeTheBalls::updateBalls() {
    for (auto& ball : m_balls) {
        cv::Point2f pos = ball->getPosition();
        pos.y += ball->getVelocityY();
        ball->setPosition(pos);
    }
}


void DodgeTheBalls::drawBalls(cv::Mat& frame) const {
    for (const auto& ball : m_balls) {
        cv::circle(frame, ball->getPosition(), ball->getRadius(), getScalarFromColor(ball->getColor()),-1);
    }
}



bool DodgeTheBalls::checkCollision(const cv::Rect& playerRect) const {
    for (const auto& ball : m_balls) {
        // Rectangle-Werte als float
        float rectX = static_cast<float>(playerRect.x);
        float rectY = static_cast<float>(playerRect.y);
        float rectWidth = static_cast<float>(playerRect.width);
        float rectHeight = static_cast<float>(playerRect.height);

        cv::Point2f pos = ball->getPosition();
        float radius = ball->getRadius();

        float closestX = std::max(rectX, std::min(pos.x, rectX + rectWidth));
        float closestY = std::max(rectY, std::min(pos.y, rectY + rectHeight));

        float distanceX = pos.x - closestX;
        float distanceY = pos.y - closestY;
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

        if (distanceSquared < (radius * radius)) {
            return true;
        }
    }
    return false;
}
void DodgeTheBalls::removeCollidedBalls(const cv::Rect& playerRect) 
{
    m_balls.erase(
        std::remove_if(m_balls.begin(), m_balls.end(),
            [&playerRect](const std::shared_ptr<Ball>& ball) 
            {
                // Rechteck-Kollisionslogik
                cv::Point2f pos = ball->getPosition();
                float radius = ball->getRadius();

                float rectX = static_cast<float>(playerRect.x);
                float rectY = static_cast<float>(playerRect.y);
                float rectWidth = static_cast<float>(playerRect.width);
                float rectHeight = static_cast<float>(playerRect.height);

                // Finde den nächsten Punkt des Rechtecks zum Mittelpunkt des Balls
                float closestX = std::max(rectX, std::min(pos.x, rectX + rectWidth));
                float closestY = std::max(rectY, std::min(pos.y, rectY + rectHeight));

                // Berechne die Distanz zwischen dem Ball-Mittelpunkt und dem nächsten Punkt
                float distanceX = pos.x - closestX;
                float distanceY = pos.y - closestY;
                float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Entferne den Ball, wenn er mit dem Rechteck kollidiert
                return distanceSquared < (radius * radius);
            }),
        m_balls.end());
}

void DodgeTheBalls::removeOffscreenBalls() {
    m_balls.erase(
        std::remove_if(m_balls.begin(), m_balls.end(),
            [this](const std::shared_ptr<Ball>& ball) {
                return ball->getPosition().y - ball->getRadius() > m_screenHeight;
            }),
        m_balls.end());
}

 const std::vector<std::shared_ptr<Ball>>& DodgeTheBalls::getBalls() const
{
    return m_balls;
}


void DodgeTheBalls::calcScore(int& m_score)
{
    for (const auto& ball : m_balls)
    {
        if (ball->getPosition().y - ball->getRadius() > m_screenHeight)
        {
            ++m_score; // Erhöhe den Score
        }
    }
}