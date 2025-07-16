#ifndef BALL_HPP
#define BALL_HPP

#include "shape.hpp"

class Ball : public Shape
{
public:
    Ball(const cv::Point2f& position, Color color, int velocity, int radius);
    virtual ~Ball();

    int getRadius() const;
    cv::Rect getRect() const;
private:
    int m_radius;
};

#endif //BALL_HPP