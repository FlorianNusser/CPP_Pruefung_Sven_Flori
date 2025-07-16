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

void DodgeTheBallsMode::update()
{
    m_logic.updateBalls();
    m_logic.calcScore(m_score);
    m_logic.removeOffscreenBalls();
}

void DodgeTheBallsMode::handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver)
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

int DodgeTheBallsMode::getScore() const {
    return m_score;
}

LeaderboardEntry DodgeTheBallsMode::getLeaderboardEntry(Player& player, int score) const {
    LeaderboardEntry entry;
    entry.playerId = player.getId();
    entry.playerName = player.getPlayername();
    entry.score = score;
    entry.userLimit = 0;
    return entry;
}