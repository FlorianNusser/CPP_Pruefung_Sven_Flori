#include "catchTheSquaresMode.hpp"
#include "constants.hpp"

CatchTheSquaresMode::CatchTheSquaresMode()
  : m_catchLogic(0, 0),
    m_dodgeLogic(0, 0),
    m_catchSpawnCounter(0),
    m_dodgeSpawnCounter(0)
{}

void CatchTheSquaresMode::initialize(int screenWidth, int screenHeight) {
    // Erzeuge beide Logik‐Instanzen mit realen Dimensionen
    m_catchLogic = CatchTheSquares(screenWidth, screenHeight);
    m_dodgeLogic = DodgeTheBalls(screenWidth, screenHeight);
}

void CatchTheSquaresMode::spawnShape() {
    // Alle CATCH_INTERVAL Frames ein Quadrat
    if (m_catchSpawnCounter++ % CatchTheSquaresConfig::SQUARE_INTERVAL == 0) {
        m_catchLogic.spawnSquares();
    }
    // Alle DODGE_INTERVAL Frames einen Ball (als Hindernis)
    if (m_dodgeSpawnCounter++ % CatchTheSquaresConfig::BALL_INTERVAL == 0) {
        m_dodgeLogic.spawnBall();
    }
}

void CatchTheSquaresMode::update(int& score) {
    // Positionen updaten
    m_catchLogic.updateSquares();
    m_dodgeLogic.updateBalls();

    // Offscreen‐Objekte entfernen
    m_catchLogic.removeOffscreenSquares();
    m_dodgeLogic.removeOffscreenBalls();
}

void CatchTheSquaresMode::handleCollisions(const std::vector<cv::Rect>& faces, int& score, bool& gameOver)
{
    for (auto const& face : faces) {
        // Gefangene Quadrate erhöhen den Score
        if (m_catchLogic.checkCollision(face)) {
            ++score;
            m_catchLogic.removeCollidedSquares(face);
        }
        // Ball‐Kollision beendet das Spiel
        else if (m_dodgeLogic.checkCollision(face)) {
            gameOver = true;
            return;
        }
    }
}

void CatchTheSquaresMode::draw(cv::Mat& frame) {
    m_catchLogic.drawSquares(frame);
    m_dodgeLogic.drawBalls(frame);
}