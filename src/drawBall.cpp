#include "drawBall.hpp"
#include "dodgeTheBalls.hpp"

DrawBall::DrawBall(const cv::Point2f& position, Color color, int velocityY)
: DrawShape(position, color, velocityY)
{

}

DrawBall::~DrawBall(){}

//vorerst weiter in DodgeTheBalls
//void DrawBall::drawShape(cv::Mat& frame) const
//{
//        for (const auto& ball : m_balls)
//        {
//                cv::circle(frame, ball.position, static_cast<int>(ball.radius), ball.color, -1);
//        }
//}
