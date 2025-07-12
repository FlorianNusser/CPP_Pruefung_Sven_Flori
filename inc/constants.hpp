#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace Constants
{
    const std::string CASCADE_FILE_PATH = "haarcascade_frontalface_default.xml";
    const int SCORE_X_COORDINATE = 10;
    const int SCORE_Y_COORDINATE = 25;
}

namespace BallConfig
{
    constexpr int MIN_RADIUS = 10;
    constexpr int MAX_RADIUS = 20;
    constexpr int MIN_VELOCITY = 5;
    constexpr int MAX_VELOCITY = 10;
    constexpr int X_SPAWN_BORDER = 20; //20, damit die Bälle nicht aus dem Bildschirm hinaus ragen
    constexpr int INITIAL_Y_POSITION = 0.0f;
}

#endif //CONSTANTS_HPP