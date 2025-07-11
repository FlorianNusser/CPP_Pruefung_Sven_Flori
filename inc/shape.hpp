#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <color.hpp>

class Shape
{
public:
    Shape(const cv::Point2f& position, Color color, float velocityY);
    virtual ~Shape();

    //Getter zu Shape
    Color getColor();
    cv::Point2f getPosition();
    float getVelocityY();


    //Setter zu Shape
    void setPosition(const cv::Point2f& pos);





protected:
    Color m_color;
    cv::Point2f m_position;
    float m_velocityY = 0.0f;
};

#endif