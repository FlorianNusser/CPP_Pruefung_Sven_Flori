#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include "color.hpp"

namespace Constants
{
    const std::string CASCADE_FILE_PATH = "haarcascade_frontalface_default.xml";
    const std::string WINDOW_NAME = "Face Detection Game";
    const int SCORE_X_COORDINATE = 10;
    const int SCORE_Y_COORDINATE = 25;
}

namespace DodgeTheBallsConfig
{
    constexpr int MIN_RADIUS = 10;
    constexpr int MAX_RADIUS = 20;
    constexpr int MIN_VELOCITY = 5;
    constexpr int MAX_VELOCITY = 10;
    constexpr int X_SPAWN_BORDER = 20; //20, damit die Bälle nicht aus dem Bildschirm hinaus ragen
    constexpr int INITIAL_Y_POSITION = 0;
    constexpr int SPAWN_INTERVAL = 30;
    constexpr Color BallColor = Color::RED;
}

namespace CatchTheSquaresConfig
{
    constexpr int MIN_SQUARE_SIZE = 20;
    constexpr int MAX_SQUARE_SIZE = 40;
    constexpr int MIN_SQUARE_VELOCITY = 2;
    constexpr int MAX_SQUARE_VELOCITY = 5;
    constexpr int SQUARE_INTERVAL = 45;
    constexpr int BALL_INTERVAL = 30;
    constexpr Color SQUARECOLOR = Color::YELLOW;
    constexpr int X_SPAWN_BORDER = 20;
}

#endif //CONSTANTS_HPP