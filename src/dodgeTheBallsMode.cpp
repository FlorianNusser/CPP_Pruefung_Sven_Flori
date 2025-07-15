#include "dodgeTheBallsMode.hpp"
#include "constants.hpp"

// Initialisiere m_logic mit Dummy-Größe; echte Werte setzt initialize()
DodgeTheBallsMode::DodgeTheBallsMode()
  : m_logic(0, 0),
    m_spawnCounter(0)
{}

void DodgeTheBallsMode::initialize(int screenWidth, int ScreenHeight)
{
    m_logic = DodgeTheBalls(screenWidth, ScreenHeight);
}

void DodgeTheBallsMode::spawnShape()
{
    if (m_spawnCounter++ % DodgeTheBallsConfig::SPAWN_INTERVAL == 0)
    {
        m_logic.spawnBall();
        ++m_spawnedShapes;
    }
}

void DodgeTheBallsMode::update(int&score)
{
    m_logic.updateBalls();
    m_logic.calcScore(score);
    m_logic.removeOffscreenBalls();
}

void DodgeTheBallsMode::handleCollisions(const std::vector<cv::Rect>& faces, int& score, bool& gameOver)
{
    for(auto&rect : faces)
    {
        if (m_logic.checkCollision(rect))
        {
            gameOver = true;
            return;
        }
    }
}

void DodgeTheBallsMode::draw(cv::Mat& frame)
{
    m_logic.drawBalls(frame);
}

//Falls man noch Counter in DodgeTheBalls will
bool DodgeTheBallsMode::isGameOver() {
    // Beispiel: Immer false, außer du willst auch für diesen Modus ein Limit
    return false;
}

int DodgeTheBallsMode::getSpawnedShapes() const {
    return m_spawnedShapes;
}

int DodgeTheBallsMode::getActiveShapes() const {
    return m_logic.getBalls().size();
}

