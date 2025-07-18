#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp> //Für die Schriftart

#include "color.hpp"

namespace Constants
{
    const std::string CASCADE_FILE_PATH = "haarcascade_frontalface_default.xml";
    const std::string WINDOW_NAME = "Face Detection Game";
    const std::string PLAYER_ID = "../playerID.txt";
    const int FRAME_WIDTH = 640;
    const int FRAME_HEIGHT = 480;
}

namespace DodgeTheBallsConfig
{
    constexpr int MIN_RADIUS            = 10;
    constexpr int MAX_RADIUS            = 20;
    constexpr int MIN_VELOCITY          = 5;
    constexpr int MAX_VELOCITY          = 10;
    constexpr int X_SPAWN_BORDER        = 20; //20, damit die Bälle nicht aus dem Bildschirm hinaus ragen
    constexpr int INITIAL_Y_POSITION    = 0;
    constexpr int SPAWN_INTERVAL        = 30;
    constexpr Color BALL_COLOR          = Color::RED;
}

namespace CatchTheSquaresConfig
{
    constexpr int MIN_SQUARE_SIZE       = 20;
    constexpr int MAX_SQUARE_SIZE       = 40;
    constexpr int MIN_SQUARE_VELOCITY   = 2;
    constexpr int MAX_SQUARE_VELOCITY   = 5;
    constexpr int SQUARE_INTERVAL       = 45;
    constexpr int BALL_INTERVAL         = 30;
    constexpr Color SQUARECOLOR         = Color::YELLOW;
    constexpr int X_SPAWN_BORDER        = 20;
}

namespace GuiConstants
{
    // -- Allgemein --
    constexpr int    FONT_FACE   = cv::FONT_HERSHEY_SIMPLEX;
    //–– Gesichtserkennung –-
    constexpr double FACE_DETECT_SCALE      = 1.1;
    constexpr int    FACE_DETECT_NEIGHBORS  = 3;
    constexpr int    FACE_DETECT_FLAGS      = 0;

    //–– Score-Anzeige (showScore) ––
    const int SCORE_X_COORDINATE = 10;
    const int SCORE_Y_COORDINATE = 25;

    //–– Game-Over-Screen ––
    constexpr int   GO_PADDING_TOP   = 50;
    constexpr int   GO_LINE_SPACING  = 20;
    constexpr char  GO_TITLE[]       = "Game Over";
    constexpr double GO_TITLE_SCALE  = 2.0;
    constexpr double GO_TEXT_SCALE   = 1.0;
    constexpr int    GO_THICKNESS    = 2;
    const     cv::Scalar GO_COLOR    = cv::Scalar(0, 0, 255);
    constexpr int    GO_BASELINE     = 0;    // wird beim getTextSize benötigt

    //–– Leaderboard-Screen ––
    constexpr double LB_TITLE_SCALE   = 1.2;
    constexpr int    LB_TITLE_Y       = 50;
    constexpr int    LB_LINE_HEIGHT    = 30;
    // Spalten-X-Koordinaten
    constexpr int    LB_COL_ID_X      = 50;
    constexpr int    LB_COL_NAME_X    = 120;
    constexpr int    LB_COL_SCORE_X   = 350;
    constexpr int    LB_COL_EXTRA_X   = 480;

    //–– Button ––
    constexpr double BTN_FONT_SCALE  = 0.8;
    constexpr int    BTN_THICKNESS   = 2;
    constexpr int    BTN_MARGIN      = 20;
    constexpr int    BTN_PAD_X       = 10;
    constexpr int    BTN_PAD_Y       = 5;
    const     cv::Scalar BTN_BG_COLOR   = cv::Scalar(255,255,255);
    const     cv::Scalar BTN_TEXT_COLOR = cv::Scalar(  0,  0,  0);
    constexpr char   BTN_ESC_TEXT[]      = "Esc: Beenden";
    constexpr char   BTN_LB_TEXT[]       = "L: Leaderboard";
}

#endif //CONSTANTS_HPP