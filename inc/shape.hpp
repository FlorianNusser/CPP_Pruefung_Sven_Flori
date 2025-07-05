#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <color.hpp>

class Shape
{
public:
    Shape();
    virtual ~Shape();
protected:
    Color m_color;
    int m_size;
    int m_velocity;
    int m_xPosition;
    int m_yPosition;

};

#endif