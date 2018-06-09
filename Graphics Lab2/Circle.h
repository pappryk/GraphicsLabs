#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Circle : public sf::CircleShape
{
public:
Circle(sf::Vector2f vec, int radius);
~Circle();
virtual void ChangeColor(int scaleColor){}
sf::CircleShape circle;
//sf::Sprite getSprite(){return sprite;}
protected:
    //sf::Uint8* pixels;
    //sf::Sprite sprite;
    sf::Image image;
    sf::Texture texture;
    unsigned int colorSize;
    int radius;
    int px;
};