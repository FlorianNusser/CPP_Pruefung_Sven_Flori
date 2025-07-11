#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

class Square : public Shape
{
public:
    Square(const cv::Point2f& position,  Color color, int velocity, int sidelength);
    virtual ~Square();

    int getSidelength() const;
    cv::Rect getRect() const;  // New Method for check Collision


private:
    int m_sidelength;
};


#endif //SQUARE_HPP