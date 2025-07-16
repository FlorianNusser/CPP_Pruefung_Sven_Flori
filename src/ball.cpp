#include "ball.hpp"
#include "shape.hpp"
#include "color.hpp"

Ball::Ball(const cv::Point2f& position, Color color, int velocityY, int radius )
    : Shape(position, color, velocityY), m_radius(radius)
{}
Ball::~Ball(){}


int Ball::getRadius() const
{
    return m_radius;
}
