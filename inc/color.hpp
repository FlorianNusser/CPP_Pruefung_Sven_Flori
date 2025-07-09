#ifndef COLOR_HPP
#define COLOR_HPP

#include <opencv2/core.hpp>
#include <stdexcept>

enum class Color{
    WHITE,
    BLACK,
    RED,
    GREEN,
    BLUE,
    PURPLE
};

cv::Scalar getScalarFromColor(Color color);

#endif