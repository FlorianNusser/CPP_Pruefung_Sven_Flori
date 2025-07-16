#ifndef CATCH_THE_SQUARES_MODE_HPP
#define CATCH_THE_SQUARES_MODE_HPP

#include "gameModeInterface.hpp"
#include "catchTheSquares.hpp"
#include "dodgeTheBalls.hpp"

class CatchTheSquaresMode : public GameModeInterface {
public:
    CatchTheSquaresMode();
    ~CatchTheSquaresMode() override = default;

    void initialize(int screenWidth, int screenHeight) override;
    void spawnShape() override;
    void update() override;
    void handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver) override;
    void draw(cv::Mat& frame) override;
    bool isGameOver() override;
    LeaderboardEntry getLeaderboardEntry(Player& player, int score) const override;

    //Getter
    int getSpawnedShapes() const override;
    int getActiveShapes() const override;
    int getScore() const override;


private:
    CatchTheSquares m_catchLogic;
    DodgeTheBalls  m_dodgeLogic;

    int m_catchSpawnCounter = 0;
    int m_dodgeSpawnCounter = 0;
    int m_spawnedShapes = 0;
    int m_shapeLimit = 0;
};

#endif //CATCH_THE_SQUARES_MODE_HPP