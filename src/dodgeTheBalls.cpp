#include "dodgeTheBalls.hpp"
#include "ball.hpp"
#include "randomGenerator.hpp"
#include "constants.hpp"
#include <algorithm>

DodgeTheBalls::DodgeTheBalls(int width, int height)
    : m_screenWidth(width), m_screenHeight(height)
{}

DodgeTheBalls::~DodgeTheBalls()
{}

void DodgeTheBalls::spawnBall() {
    std::uniform_int_distribution<int> radiusDist(BallConfig::MIN_RADIUS,BallConfig::MAX_RADIUS);
    std::uniform_int_distribution<int> velocityDist(BallConfig::MIN_VELOCITY, BallConfig::MAX_VELOCITY);
    std::uniform_int_distribution<int> xSpawnDist(BallConfig::X_SPAWN_BORDER, m_screenWidth - BallConfig::X_SPAWN_BORDER);

    float velocityY = velocityDist(RandomGenerator::getGenerator());
    float radius = radiusDist(RandomGenerator::getGenerator());
    const cv::Point2f position = cv::Point2f(xSpawnDist(RandomGenerator::getGenerator()), 0);
    Color color = Color::RED;
    cv::Scalar scalarColor = getScalarFromColor(color);
    auto ball = std::make_shared<Ball>(position, color,velocityY, radius);
    m_balls.push_back(ball);
}

void DodgeTheBalls::updateBalls() {
    for (auto& ball : m_balls) {
        cv::Point2f pos = ball->getPosition();
        pos.y += ball->getVelocityY();
        ball->setPosition(pos);
    }
}

//bald in drawballs //warum den Radius nicht gleich auf Int setzen?
void DodgeTheBalls::drawBalls(cv::Mat& frame) const {
    for (const auto& ball : m_balls) {
        cv::circle(frame, ball->getPosition(), static_cast<int>(ball->getRadius()), getScalarFromColor(ball->getColor()),-1);
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

void DodgeTheBalls::removeOffscreenBalls() {
    m_balls.erase(
        std::remove_if(m_balls.begin(), m_balls.end(),
            [this](const std::shared_ptr<Ball>& ball) {
                return ball->getPosition().y - ball->getRadius() > m_screenHeight;
            }),
        m_balls.end());
}

const std::vector<std::shared_ptr<Ball>>& DodgeTheBalls::getBalls() const {
    return m_balls;
}