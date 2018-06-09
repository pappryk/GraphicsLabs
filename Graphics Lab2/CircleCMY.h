#pragma once
#include "Circle.h"
#include "math.h"

class CircleCMY : public Circle
{
public:
    void ChangeColor(float scaleColor);
    CircleCMY(sf::Vector2f vec, int radius);
};

sf::Color cmy(float C, float M, float Y);
