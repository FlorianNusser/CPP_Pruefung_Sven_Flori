#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class shape
{
public:
    shape::shape(std::string color);
    virtual shape::~shape();
private:
    std::string m_color;

};

#endif