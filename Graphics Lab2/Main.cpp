#include "Main.h"
#include <iostream>

int main()
{
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    sf::Event event;
    const unsigned int radius = 120, spacing = 30, circlePoints = 30;
    unsigned int FPS = 0 , frame_counter = 0;
    bool changed = false;
    sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::RenderTexture texture;
    texture.create(800, 650);
    sf::Sprite sprite;
    sf::RectangleShape changer;
    changer.setPosition(4 * radius + 4 * spacing, (int)spacing / 2);
    changer.setSize(sf::Vector2f(50, 250));
    changer.setFillColor(sf::Color::Red);

    float changerValue = 0.5;


    //Initialize circles
    
    CircleHSL circleHSL(sf::Vector2f(spacing, spacing), radius);
    CircleHSV circleHSV(sf::Vector2f(spacing * 2 + radius * 2, spacing), radius);
    CircleCMY circleCMY(sf::Vector2f(spacing, spacing * 2 + radius * 2), radius);
    CircleRGB circleRGB(sf::Vector2f(spacing * 2 + radius * 2, spacing * 2 + radius * 2), radius);

    //circleHSL.setFillColor(sf::Color::Red);
    //circleHSV.setFillColor(sf::Color::Red);
    //circleCMY.setFillColor(sf::Color::Red);
    //circleRGB.setFillColor(sf::Color(0, 0, 0, 0));


    DrawToTexture(texture, circleHSL, circleHSV, circleCMY, circleRGB, changerValue);
    texture.display();
    
    window.setFramerateLimit(30);
    

    clock.restart().asMilliseconds();
    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                sf::Mouse::getPosition().x - window.getPosition().x >= changer.getPosition().x &&
                sf::Mouse::getPosition().x - window.getPosition().x <= changer.getPosition().x + changer.getSize().x &&
                sf::Mouse::getPosition().y - window.getPosition().y >= changer.getPosition().y &&
                sf::Mouse::getPosition().y - window.getPosition().y <= changer.getPosition().y + changer.getSize().y)
            {
                changed = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                changed = false;
            }
            changerValue = (sf::Mouse::getPosition().y - window.getPosition().y - spacing / 2) / changer.getSize().y;            
            //std::cout << (event.mouseMove.y - spacing / 2) / changer.getSize().y << std::endl;
            //std::cout << changerValue << std::endl;
            
        }

        // Drawing
        if (changed)
        {
            texture.clear(sf::Color::White);
            DrawToTexture(texture, circleHSL, circleHSV, circleCMY, circleRGB, changerValue);
            texture.display();
        }
        sprite.setTexture(texture.getTexture());
        window.draw(sprite);
        window.draw(changer);
        
        //FPS counter
        if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
            clock.restart();
            frame_counter = 0;
        }
        frame_counter++;

        window.display();
    }
}