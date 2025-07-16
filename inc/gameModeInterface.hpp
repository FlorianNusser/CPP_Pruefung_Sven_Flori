#ifndef GAME_MODE_INTERFACE
#define GAME_MODE_INTERFACE

#include <opencv2/opencv.hpp>
#include <vector>

class GameModeInterface
{
public:
    virtual ~GameModeInterface();

    virtual void initialize(int screenwidth, int screenheight) = 0;
    virtual void spawnShape() = 0;
    virtual void update() = 0;
    virtual void handleCollisions(const std::vector<cv::Rect>& faces, bool& gameOver) = 0;
    virtual void draw(cv::Mat& frame) = 0;

    //Getter
    virtual int getScore() const = 0;

    //Object Counters
    virtual int getSpawnedShapes() const = 0;
    virtual int getActiveShapes() const = 0;
    virtual bool isGameOver() = 0;
protected:
    int m_score = 0;
};



#endif //GAME_MODE_INTERFACE
