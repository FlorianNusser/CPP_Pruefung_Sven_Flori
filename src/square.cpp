#include "square.hpp"
#include "shape.hpp"
#include "color.hpp"

Square::Square(const cv::Point2f& position, Color color, int velocityY,int sidelength)
    : Shape(position, color, velocityY), m_sidelength(sidelength)
{}
Square::~Square(){}


int Square::getSidelength() const
{
    return m_sidelength;
}

cv::Rect Square::getRect() const
{
    // Convert float position to int for Rect
    int x = static_cast<int>(m_position.x);
    int y = static_cast<int>(m_position.y);
    return cv::Rect(x, y, m_sidelength, m_sidelength);
}