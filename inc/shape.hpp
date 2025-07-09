#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <color.hpp>

class Shape
{
public:
    Shape(const cv::Point2f& position, Color color);
    virtual ~Shape();

    virtual void drawShape() = 0;

protected:
    Color m_color;
    cv::Point2f m_position;
    float m_velocityY;
};

#endif