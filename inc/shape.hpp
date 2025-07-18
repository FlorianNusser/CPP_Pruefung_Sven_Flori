#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <color.hpp>

class Shape
{
public:
    Shape(const cv::Point2f& position, Color color, int velocityY);
    virtual ~Shape();

    //Getter for Shape
    Color getColor();
    cv::Point2f getPosition();
    int getVelocityY();


    //Setter for Shape
    void setPosition(const cv::Point2f& pos);





protected:
    Color m_color;
    cv::Point2f m_position;
    int m_velocityY = 0;
};

#endif