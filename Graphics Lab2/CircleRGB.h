#pragma once
#include "Circle.h"

class CircleRGB : public Circle
{
public:
    void ChangeColor(float scaleColor);
    CircleRGB(sf::Vector2f vec, int radius);
};