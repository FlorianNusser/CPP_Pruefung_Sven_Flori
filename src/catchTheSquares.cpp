#include "catchTheSquares.hpp"
#include "square.hpp"
#include "randomGenerator.hpp"
#include <algorithm>

CatchTheSquares::CatchTheSquares(int width, int height): m_screenWidth(width), m_screenHeight(height)
{
}

CatchTheSquares::~CatchTheSquares()
{
}

void CatchTheSquares::spawnSquares() {
    std::uniform_int_distribution<int> sizeDist(20, 40);  // Zufällige Größe der Quadrate
    std::uniform_real_distribution<float> velocityDist(2.0f, 5.0f);  // Fallgeschwindigkeit
    std::uniform_real_distribution<float> xDist(0.0f, m_screenWidth - 40.0f);  // Startposition X
    
    int size = sizeDist(RandomGenerator::getGenerator());
    float velocityY = velocityDist(RandomGenerator::getGenerator());
    float x = xDist(RandomGenerator::getGenerator());
    
    // Quadrat oben am Bildschirmrand spawnen
    cv::Point2f position(x, 0.0f);
    Color color = Color::GREEN;  // Quadrate in Grün
    auto square = std::make_shared<Square>(position, color, velocityY, size);
    
    m_squares.push_back(square);
}

void CatchTheSquares::updateSquares() {
    for (auto& square : m_squares) {
        cv::Point2f pos = square->getPosition();
        pos.y += square->getVelocityY();
        square->setPosition(pos);
    }
}

void CatchTheSquares::drawSquares(cv::Mat& frame) const {
    for (const auto& square : m_squares) {
        cv::Rect rect = square->getRect();
        cv::rectangle(frame, rect, getScalarFromColor(square->getColor()), cv::FILLED);
    }
}

bool CatchTheSquares::checkCollision(const cv::Rect& playerRect) const {
    for (const auto& square : m_squares) {
        cv::Rect squareRect = square->getRect();
        if ((playerRect & squareRect).area() > 0) {
            return true;
        }
    }
    return false;
}


void CatchTheSquares::removeOffscreenSquares() 
{
    m_squares.erase(
        std::remove_if(m_squares.begin(), m_squares.end(),
            [this](const std::shared_ptr<Square>& square) {
                return square->getPosition().y > m_screenHeight;
            }),
        m_squares.end());
}

void CatchTheSquares::removeCollidedSquares(const cv::Rect& playerRect) {
    m_squares.erase(
        std::remove_if(m_squares.begin(), m_squares.end(),
            [&playerRect](const std::shared_ptr<Square>& square) {
                cv::Rect squareRect = square->getRect();
                return (playerRect & squareRect).area() > 0; // Kollisionsprüfung
            }),
        m_squares.end());
}