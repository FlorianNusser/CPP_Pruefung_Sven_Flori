#include "shape.hpp"
#include <iostream>
#include "color.hpp"
Shape::Shape(const cv::Point2f& position, Color color, float velocityY)
    : m_position(position), m_color(color), m_velocityY(velocityY)
{

}

Shape::~Shape()
{
}


Color Shape::getColor()
{
    return m_color;
}

float Shape::getVelocityY()
{
    return m_velocityY;
}

cv::Point2f Shape::getPosition()
{
    return m_position;
}

void Shape::setPosition(const cv::Point2f& pos)
{
    m_position = pos;
}