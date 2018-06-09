#include "CircleRGB.h"
#include "math.h"

CircleRGB::CircleRGB(sf::Vector2f vec, int radius) : Circle(vec, radius)
{
    
}

void CircleRGB::ChangeColor(float scaleColor)
{
    for (int i = 0; i < px; i++)
    {
        for (int j = 0; j < radius; j++)
        {
            image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, sf::Color(255 * j / radius, 255 - 255 *i / px, 255 * scaleColor , 255));
        }
    }
    texture.loadFromImage(image);
    this->setTexture(&texture);
}