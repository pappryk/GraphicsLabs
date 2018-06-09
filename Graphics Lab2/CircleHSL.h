#pragma once
#include "Circle.h"
#include "math.h"

class CircleHSL : public Circle
{
public:
    void ChangeColor(float scaleColor);
    CircleHSL(sf::Vector2f vec, int radius);
};

sf::Color hsl(float H, float S, float L);
float Hue_2_RGB(float v1, float v2, float vH );

int maxRGB(int r, int g, int b);
int minRGB(int r, int g, int b);
int midRGB(int r, int g, int b);



