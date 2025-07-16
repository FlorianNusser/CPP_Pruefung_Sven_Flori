#ifndef DODGE_THE_BALLS_MODE_HPP
#define DODGE_THE_BALLS_MODE_HPP

#include "gameModeInterface.hpp"
#include "dodgeTheBalls.hpp"

class DodgeTheBallsMode : public GameModeInterface {
public:
    DodgeTheBallsMode();
    void initialize(int w, int h) override;
    void spawnShape() override;
    void update() override;
    void handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver) override;
    void draw(cv::Mat& frame) override;


    bool isGameOver() override;
    int getSpawnedShapes() const override;
    int getActiveShapes() const override;
    int getScore() const override;

private:
    DodgeTheBalls m_logic;
    int m_spawnCounter = 0;
    int m_spawnedShapes = 0;
};




#endif //DODGE_THE_BALLS_MODE_HPP