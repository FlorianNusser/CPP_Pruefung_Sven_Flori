#ifndef DRAW_BALL_HPP
#define DRAW_BALL_HPP

#include "drawShape.hpp"
#include "color.hpp"
#include <opencv2/opencv.hpp>

class DrawBall : public DrawShape
{
public:
    DrawBall(const cv::Point2f& position, Color color, int velocityY);

    virtual ~DrawBall();

    //void drawShape(cv::Mat& frame) const override;
    void moveShape();



    void setSpeed(float speed)
    {
        m_velocityY = speed;
    }
private:

};

#endif // DRAW_BALL_HPP