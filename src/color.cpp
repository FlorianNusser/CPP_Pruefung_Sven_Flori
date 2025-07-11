#include "color.hpp"

cv::Scalar getScalarFromColor(Color color) {
    switch (color) {
        case Color::WHITE:
            return cv::Scalar(255, 255, 255);
        case Color::BLACK:
            return cv::Scalar(0, 0, 0);
        case Color::RED:
            return cv::Scalar(0, 0, 255);
        case Color::GREEN:
            return cv::Scalar(0, 255, 0);
        case Color::BLUE:
            return cv::Scalar(255, 0, 0);
        case Color::PURPLE:
            return cv::Scalar(255, 0, 255); // Magenta als Purple
        default:
            throw std::runtime_error("Unknown Color enum value");
    }
}