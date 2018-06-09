#pragma once
#include "Circle.h"
#include "math.h"

class CircleHSV : public Circle
{
public:
    void ChangeColor(float scaleColor);
    CircleHSV(sf::Vector2f vec, int radius);
};
sf::Color hsv(int hue, float sat, float val);