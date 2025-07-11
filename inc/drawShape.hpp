#ifndef DRAW_SHAPE_HPP
#define DRAW_SHAPE_HPP

#include "shape.hpp"

class DrawShape : public Shape
{
public:
    DrawShape(const cv::Point2f& position, Color color, int velocityY);

    virtual ~DrawShape();

    virtual void drawShape(cv::Mat& frame) const = 0;

    //Setter
    void setSpeed();

private:
};

#endif //DRAW_SHAPE_HPP