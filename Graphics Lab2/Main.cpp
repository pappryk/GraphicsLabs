#include "Main.h"

int main()
{
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    unsigned int FPS = 0 , frame_counter = 0;
    sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);

    clock.restart().asMilliseconds();
    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::White);

        while (window.pollEvent(event))
        {
        // zdarzenia
        }
        //tu wyrysować wszystko na ekran

        //tu wypisać na ekran wartość FPS
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