#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>



void KeyEvent(sf::Event& event, wchar_t& flag)
{

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
  {
    flag = 'l';
  }  

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
  {
    flag = 'r';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    flag = 'a';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
  {
    flag = 'c';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    flag = 'w';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
  {
    flag = 'o';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
  {
    flag = 'b';
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
  {
    flag = 'f';
  }
}



void DrawRect(sf::RectangleShape& rectangle, sf::RenderWindow& window, wchar_t& flag, sf::Color& mcolor, sf::Color& fcolor)
{
    rectangle.setOutlineColor(mcolor);  
    if (flag == 'r')
    {
        rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    }
    else
    {
        rectangle.setFillColor(fcolor);
    }
    rectangle.setSize(sf::Vector2f(sf::Mouse::getPosition().x - window.getPosition().x - rectangle.getPosition().x,
                      sf::Mouse::getPosition().y - window.getPosition().y - rectangle.getPosition().y));
}



void DrawCircle(sf::CircleShape& circle, sf::RenderWindow& window, sf::Color& color)
{
    float xRad = sf::Mouse::getPosition().x - window.getPosition().x - circle.getPosition().x;
    float yRad = sf::Mouse::getPosition().y - window.getPosition().y - circle.getPosition().y;
    float radius;
    if(xRad + yRad >= 0)
    {
        radius = (sqrt(xRad * xRad + yRad * yRad));
    }
    else
    {
        radius = - sqrt(xRad * xRad + yRad * yRad);        
    }
    circle.setOutlineColor(color);
    circle.setRadius(radius);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}



void DrawLine(sf::VertexArray& line, sf::RenderWindow& window, sf::Color& mcolor, sf::Color& fcolor)
{
    line[1].position = sf::Vector2f(sf::Mouse::getPosition().x - window.getPosition().x ,
                                    sf::Mouse::getPosition().y - window.getPosition().y);
    line[0].color = mcolor;
    line[1].color = fcolor;
}


void GetColor(float x, float y, sf::Color& color)
{
  if (y < 30)
  {
    if (x < 255)
    {
      color = sf::Color(x, 255, 0);
    }
    else if (x < 510)
    {
      color = sf::Color(255, 255 - x, 0);
    }
    else
    {
      color = sf::Color(255, 0, x);
    }
  }
  else
  {
    if (x < 255)
    {
      color = sf::Color(0, 255, x);
    }
    else if (x < 510)
    {
      color = sf::Color(0, 509 - x, 255);
    }
    else
    {
      color = sf::Color(510 + x, 0, 255);
    }
  }

}