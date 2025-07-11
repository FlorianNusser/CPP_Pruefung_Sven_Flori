#include "ball.hpp"
#include "shape.hpp"
#include "color.hpp"

Ball::Ball(const cv::Point2f& position, float radius, Color color, float velocityY)
    : Shape(position, color, velocityY), m_radius(radius)
{}
Ball::~Ball(){}


float Ball::getRadius() const
{
    return m_radius;
}
