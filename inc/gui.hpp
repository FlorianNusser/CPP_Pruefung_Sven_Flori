#ifndef GUI_HPP
#define GUI_HPP

#include <opencv2/opencv.hpp>
#include <string>

#include "player.hpp"
#include "gamemode.hpp"
#include "color.hpp"
#include "dodgeTheBalls.hpp"
#include "constants.hpp"

class Game; //Forward declaration

//Anchor for Button
enum class Anchor { BottomLeft, BottomRight };

class Gui
{
public:
    Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode);
    virtual ~Gui();


    bool initialize();
    void display();

    std::vector<cv::Rect> updateFrame(cv::Mat& frame);

    int getKeyboard();

    void showScore(cv::Mat& frame, int score);
    void showGameOver(cv::Mat &frame, int score, Player player);
    void showLeaderboard(cv::Mat& frame);
    void drawButton(cv::Mat& frame, const std::string& text, Anchor anchor);

private:
    cv::CascadeClassifier faceCascade;
    int m_frameWidth;
    int m_frameHeight;
    Color m_textcolor;
    Game &m_game;
    Playmode m_playmode;
    std::vector<cv::Rect> m_lastFaces;

    static std::vector<std::vector<std::string>> parseLeaderboardFile(const std::string& filename, Playmode mode);
};



#endif //GUI_HPP