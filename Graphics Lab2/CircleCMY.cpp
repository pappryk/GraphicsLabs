#include "CircleCMY.h"
#include <iostream>

CircleCMY::CircleCMY(sf::Vector2f vec, int radius) : Circle(vec, radius)
{
    
}

void CircleCMY::ChangeColor(float scaleColor)
{
    for (int i = 0; i < px; i++)
    {
        for (int j = 0; j < radius; j++)
        {
            //image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, cmy(i / px, j / radius, scaleColor ));
            image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, cmy(255 * j / radius, 255 - 255 *i / px, 255 * scaleColor));     
        }
    }
    texture.loadFromImage(image);
    //texture.update(pixels);
    this->setTexture(&texture);
    //sprite.setTexture(texture);
}

sf::Color cmy(float C, float M, float Y)
{/*
    int R = (1.0 - C) * 255;
    int G = (1.0 - M) * 255;
    int B = (1.0 - Y) * 255;*/
    int R = 255 - C;
    int G = 255 - M;
    int B = 255 - Y;
    std::cout << R << " " << G << " " << B << std::endl;    
    return sf::Color(R, G, B);
}