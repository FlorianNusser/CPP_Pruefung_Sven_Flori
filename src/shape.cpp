#include "shape.hpp"
#include <iostream>
#include "color.hpp"
Shape::Shape(const cv::Point2f& position, Color color)
    : m_position(position), m_color(color)
{

}

Shape::~Shape()
{
}