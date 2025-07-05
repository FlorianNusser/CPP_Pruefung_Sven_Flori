#ifndef BALL_HPP
#define BALL_HPP

#include <opencv2/opencv.hpp>

struct Ball {
  cv::Point2f pos;
  cv::Point2f vel;
  float radius;

  Ball(cv::Point2f p, cv::Point2f v, float r)
    : pos(p), vel(v), radius(r) {}
  void update(float dt) { pos += vel * dt; }
  bool offScreen(int h) const { return pos.y - radius > h; }
};

#endif // BALL_HPP