#include "Circle.h"
#include <math.h>

Circle::Circle(sf::Vector2f vec, int radius) : CircleShape(radius)
{
    px = 1600;
    colorSize = 2 * radius;
    //pixels = new sf::Uint8 [4 * radius * radius * 4];
    this->setPosition(vec);
    this->radius = radius;
    image.create(radius * 2, radius * 2, sf::Color(0,0,0,0));

}

Circle::~Circle()
{
    //delete [] pixels;
}

