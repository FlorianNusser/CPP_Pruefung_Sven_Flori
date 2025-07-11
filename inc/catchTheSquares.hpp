#ifndef CATCH_THE_SQUARES_HPP
#define CATCH_THE_SQUARES_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <square.hpp>


class CatchTheSquares
{
public:
CatchTheSquares(int width, int height);
virtual ~CatchTheSquares();

void spawnSquares();
void updateSquares();

void drawSquares(cv::Mat& frame) const;
bool checkCollision(const cv::Rect& playerRect) const;
void removeOffscreenSquares();

void removeCollidedSquares(const cv::Rect& playerRect);

private:
std::vector<std::shared_ptr<Square>> m_squares;
int m_screenWidth;
int m_screenHeight;

};

#endif