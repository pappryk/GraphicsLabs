#include "Functions.h"
#include <iostream>


void DrawToTexture(sf::RenderTexture& texture, CircleHSL& circleHSL, CircleHSV& circleHSV, CircleCMY& circleCMY, CircleRGB& circleRGB, float scaleColor)
{
    circleHSL.ChangeColor(scaleColor);    
    texture.draw(circleHSL);
    circleHSV.ChangeColor(scaleColor);
    texture.draw(circleHSV);
    circleCMY.ChangeColor(scaleColor);
    texture.draw(circleCMY);
    circleRGB.ChangeColor(scaleColor);
    texture.draw(circleRGB);
    
}
