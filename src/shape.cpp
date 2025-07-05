#include "shape.hpp"
#include <iostream>
#include <random>

//Statischer Generator welcher Zufallszahlen generiert (soll nicht jedes Mal im Konstruktor erneut initialisiert werden)
static std::mt19937& getGenerator()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

Shape::Shape() : m_color(Color::Red), m_yPosition(0)
{
    std::uniform_int_distribution<int> sizeDist(10, 100);
    std::uniform_int_distribution<int> velocityDist(1, 10);
    std::uniform_int_distribution<int> positionDist(0, 500);

    m_size = sizeDist(getGenerator());
    m_velocity = velocityDist(getGenerator());
    m_xPosition = positionDist(getGenerator());
}

Shape::~Shape()
{
}