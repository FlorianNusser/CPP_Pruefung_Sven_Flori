#ifndef DRAW_SHAPE_HPP
#define DRAW_SHAPE_HPP

#include "shape.hpp"

class DrawShape : public Shape
{
public:
    DrawShape(const cv::Point2f& position, Color color, float velocityY);

    virtual ~DrawShape() {}

    void drawShape() override
    {
        // Hier könnte die Logik zum Zeichnen der Form implementiert werden
        // Zum Beispiel: cv::circle(frame, m_position, m_size, getScalarFromColor(m_color), -1);
        std::cout << "Drawing shape at position: " << m_position << " with color: " << static_cast<int>(m_color) << std::endl;
    }
private:
};

#endif //DRAW_SHAPE_HPP