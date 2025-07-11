#ifndef BALL_HPP
#define BALL_HPP

#include "shape.hpp"

class Ball : public Shape
{
public:
    Ball(const cv::Point2f& position, float velocity, Color color, float radius);
    virtual ~Ball();

    float getRadius() const;

private:
    float m_radius;
};

#endif //BALL_HPP