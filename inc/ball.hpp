#ifndef BALL_HPP
#define BALL_HPP

#include "shape.hpp"

class Ball : public Shape
{
public:
    Ball(const cv::Point2f& position, float radius, Color color);
    virtual ~Ball();

    void drawShape() override;

private:
    float m_radius;
};

#endif //BALL_HPP