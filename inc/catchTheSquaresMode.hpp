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
    void update(int& score) override;
    void handleCollisions(const std::vector<cv::Rect>& faces, int& score, bool& gameOver) override;
    void draw(cv::Mat& frame) override;

private:
    CatchTheSquares m_catchLogic;
    DodgeTheBalls  m_dodgeLogic;

    int m_catchSpawnCounter = 0;
    int m_dodgeSpawnCounter = 0;
};

#endif //CATCH_THE_SQUARES_MODE_HPP