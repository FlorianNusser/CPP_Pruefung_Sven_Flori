#include "catchTheSquaresMode.hpp"
#include "constants.hpp"

CatchTheSquaresMode::CatchTheSquaresMode()
  : m_catchLogic(0, 0),
    m_dodgeLogic(0, 0, Playmode::CatchTheSquares, false),
    m_catchSpawnCounter(0),
    m_dodgeSpawnCounter(0)
{
}

void CatchTheSquaresMode::initialize(int screenWidth, int screenHeight)
{
// Create both logic instances with real dimensions
    m_catchLogic = CatchTheSquares(screenWidth, screenHeight);

    m_dodgeLogic = DodgeTheBalls(screenWidth, screenHeight, Playmode::CatchTheSquares);

    
    std::cout << "How many Shapes do you want to be spawned: ";
    std::cin >> m_shapeLimit;
    std::cout << std::endl;

}

void CatchTheSquaresMode::spawnShape() {
    // all CATCH_INTERVAL frames one Square


    if (m_catchSpawnCounter++ % CatchTheSquaresConfig::SQUARE_INTERVAL == 0 && m_shapeLimit > m_spawnedShapes) 
    {
        m_catchLogic.spawnSquares();
        ++m_spawnedShapes;
    }
    // all DODGE_INTERVAL frames one Ball (as obstacle)
    if (m_dodgeSpawnCounter++ % CatchTheSquaresConfig::BALL_INTERVAL == 0 && m_shapeLimit > m_spawnedShapes) 
    {
        m_dodgeLogic.spawnBall();
        ++m_spawnedShapes;
    }
}

void CatchTheSquaresMode::update()
{
    // update position
    m_catchLogic.updateSquares();
    m_dodgeLogic.updateBalls();

    // remove offscreen objects
    m_catchLogic.removeOffscreenSquares();
    m_dodgeLogic.removeOffscreenBalls();
}

void CatchTheSquaresMode::handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver)
{
    for (auto const& face : faces)
    {
        // caught squares increase the score
        if (m_catchLogic.checkCollision(face))
        {
            ++m_score;
            m_catchLogic.removeCollidedSquares(face);
        }
        // ball collision ends the game
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

LeaderboardEntry CatchTheSquaresMode::getLeaderboardEntry(Player& player, int score) const {
    LeaderboardEntry entry;
    entry.playerId = player.getId();
    entry.playerName = player.getPlayername();
    entry.score = score;
    entry.userLimit = m_shapeLimit;
    return entry;
}