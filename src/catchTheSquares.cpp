#include "catchTheSquares.hpp"
#include "square.hpp"
#include "randomGenerator.hpp"
#include "constants.hpp"
#include <algorithm>

CatchTheSquares::CatchTheSquares(int width, int height): m_screenWidth(width), m_screenHeight(height)
{
}

CatchTheSquares::~CatchTheSquares()
{
}

void CatchTheSquares::spawnSquares()
{
    std::uniform_int_distribution<int> squareSizeDist(CatchTheSquaresConfig::MIN_SQUARE_SIZE, CatchTheSquaresConfig::MAX_SQUARE_SIZE);  // Zufällige Größe der Quadrate
    std::uniform_int_distribution<int> velocityYDist(CatchTheSquaresConfig::MIN_SQUARE_VELOCITY, CatchTheSquaresConfig::MAX_SQUARE_VELOCITY);  // Fallgeschwindigkeit
    std::uniform_int_distribution<int> xSpawnDist(CatchTheSquaresConfig::X_SPAWN_BORDER, m_screenWidth - CatchTheSquaresConfig::X_SPAWN_BORDER);  // Startposition X

    int velocityY = velocityYDist(RandomGenerator::getGenerator());
    int size = squareSizeDist(RandomGenerator::getGenerator());
    // Quadrat oben am Bildschirmrand spawnen
    cv::Point2f position(xSpawnDist(RandomGenerator::getGenerator()), 0);
    auto square = std::make_shared<Square>(position, CatchTheSquaresConfig::SQUARECOLOR, velocityY, size);
    m_squares.push_back(square);
}

void CatchTheSquares::updateSquares()
{
    for (auto& square : m_squares)
    {
        cv::Point2f pos = square->getPosition();
        pos.y += square->getVelocityY();
        square->setPosition(pos);
    }
}

void CatchTheSquares::drawSquares(cv::Mat& frame) const
{
    for (const auto& square : m_squares)
    {
        cv::Rect rect = square->getRect();
        cv::rectangle(frame, rect, getScalarFromColor(square->getColor()), cv::FILLED);
    }
}

bool CatchTheSquares::checkCollision(const cv::Rect& playerRect) const
{
    for (const auto& square : m_squares)
    {
        cv::Rect squareRect = square->getRect();
        if ((playerRect & squareRect).area() > 0)
        {
            return true;
        }
    }
    return false;
}


void CatchTheSquares::removeOffscreenSquares()
{
    m_squares.erase(
        std::remove_if(m_squares.begin(), m_squares.end(),
            [this](const std::shared_ptr<Square>& square) 
            {
                return square->getPosition().y > m_screenHeight;
            }),
        m_squares.end());
}

void CatchTheSquares::removeCollidedSquares(const cv::Rect& playerRect) 
{
    m_squares.erase(
        std::remove_if(m_squares.begin(), m_squares.end(),
            [&playerRect](const std::shared_ptr<Square>& square) 
            {
                cv::Rect squareRect = square->getRect();
                return (playerRect & squareRect).area() > 0; // Kollisionsprüfung
            }),
        m_squares.end());
}


const std::vector<std::shared_ptr<Square>>& CatchTheSquares::getSquares() const
{
    return m_squares;
}