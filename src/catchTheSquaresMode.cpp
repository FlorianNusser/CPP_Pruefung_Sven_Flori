#include "catchTheSquaresMode.hpp"
#include "constants.hpp"

CatchTheSquaresMode::CatchTheSquaresMode()
  : m_catchLogic(0, 0),
    m_dodgeLogic(0, 0, Playmode::DodgeTheBalls, false),
    m_catchSpawnCounter(0),
    m_dodgeSpawnCounter(0)
{
    std::cout << "How many Shapes do you want to be spawned: ";
    std::cin >> m_shapeLimit;
    std::cout << std::endl;
}

void CatchTheSquaresMode::initialize(int screenWidth, int screenHeight)
{
    // Erzeuge beide Logik‐Instanzen mit realen Dimensionen
    m_catchLogic = CatchTheSquares(screenWidth, screenHeight);
    m_dodgeLogic = DodgeTheBalls(screenWidth, screenHeight, Playmode::DodgeTheBalls);
}

void CatchTheSquaresMode::spawnShape() {
    // Alle CATCH_INTERVAL Frames ein Quadrat


    if (m_catchSpawnCounter++ % CatchTheSquaresConfig::SQUARE_INTERVAL == 0 && m_shapeLimit > m_spawnedShapes) 
    {
        m_catchLogic.spawnSquares();
        ++m_spawnedShapes;
    }
    // Alle DODGE_INTERVAL Frames einen Ball (als Hindernis)
    if (m_dodgeSpawnCounter++ % CatchTheSquaresConfig::BALL_INTERVAL == 0 && m_shapeLimit > m_spawnedShapes) 
    {
        m_dodgeLogic.spawnBall();
        ++m_spawnedShapes;
    }
}

void CatchTheSquaresMode::update()
{
    // Positionen updaten
    m_catchLogic.updateSquares();
    m_dodgeLogic.updateBalls();

    // Offscreen‐Objekte entfernen
    m_catchLogic.removeOffscreenSquares();
    m_dodgeLogic.removeOffscreenBalls();
}

void CatchTheSquaresMode::handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver)
{
    for (auto const& face : faces)
    {
        // Gefangene Quadrate erhöhen den Score
        if (m_catchLogic.checkCollision(face))
        {
            ++m_score;
            m_catchLogic.removeCollidedSquares(face);
        }
        // Ball‐Kollision beendet das Spiel
        else if (m_dodgeLogic.checkCollision(face))
        {
            m_dodgeLogic.removeCollidedBalls(face);
            if(m_score > 0)
            {
                --m_score;
            }
        }
    }
}

void CatchTheSquaresMode::draw(cv::Mat& frame)
{
    m_catchLogic.drawSquares(frame);
    m_dodgeLogic.drawBalls(frame);
}

int CatchTheSquaresMode::getSpawnedShapes() const
{
    return m_spawnedShapes;
}
int CatchTheSquaresMode::getActiveShapes() const
{
    return m_catchLogic.getSquares().size() + m_dodgeLogic.getBalls().size();
}

bool CatchTheSquaresMode::isGameOver()
{
    return (m_spawnedShapes >= m_shapeLimit) && (getActiveShapes() == 0);
}

int CatchTheSquaresMode::getScore() const {
    return m_score;
}