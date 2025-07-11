#include "drawShape.hpp"


DrawShape::DrawShape(const cv::Point2f& position, Color color, float velocityY)
    : Shape(position, color, velocityY)
{
}

DrawShape::~DrawShape() {}