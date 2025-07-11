#include "drawShape.hpp"


DrawShape::DrawShape(const cv::Point2f& position, Color color, int velocityY)
    : Shape(position, color, velocityY)
{
}

DrawShape::~DrawShape() {}