#include "ball.hpp"
#include "shape.hpp"
#include "color.hpp"

Ball::Ball(const cv::Point2f& position, float radius, Color color)
    : Shape(position, color), m_radius(radius)
{}
Ball::~Ball(){}

void Ball::drawShape()
{
    cv::Scalar cvColor = getScalarFromColor(m_color);
}