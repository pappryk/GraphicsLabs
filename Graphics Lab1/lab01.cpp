// Calosc mozna dowolnie edytowac wedle uznania. 
#define WIDTH  2
#define HEIGHT 62

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "font.h"
#include "Functions.h"

wchar_t flag = L' ';



class Menu : public sf::Drawable
{
 private:
  sf::Font font;
  sf::Text* text;
  sf::RectangleShape* rectangle;
  
  sf::Texture *colors_texture;
  sf::Sprite *colors_sprite;
  sf::Uint8 *colors_pixels;
  const unsigned int colors_size_x = 765;
  const unsigned int colors_size_y = 60;

  inline void draw_to_color_pixels(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b)
  {
   colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
   colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
   colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
   colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
  }

 public:
  Menu()
  {
   font.loadFromMemory(font_data, font_data_size);
   text = new sf::Text;
   text->setFont(font);
   text->setCharacterSize(12);
   text->setFillColor(sf::Color::White);

   rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
   rectangle->setFillColor(sf::Color::Transparent);
   rectangle->setOutlineColor(sf::Color::White);
   rectangle->setOutlineThickness(1.0f);
   rectangle->setPosition(2, 62);

   unsigned int x, y;
   colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
   for (x = 0; x<255; x++)
    for (y = 0; y < 30; y++)
     {
      draw_to_color_pixels(x, y, x, 255, 0);
      draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
      draw_to_color_pixels(x + 510, y, 255, 0, x);
      draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
      draw_to_color_pixels(509 - x, y + 30, 0, x, 255 );
      draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
     }

    colors_texture = new sf::Texture();
    colors_texture->create(colors_size_x, colors_size_y);
    colors_texture->update(colors_pixels);

    colors_sprite = new sf::Sprite();
    colors_sprite->setTexture(*colors_texture);
    colors_sprite->setPosition(1, 1);
  }

  void outtextxy(sf::RenderTarget& target, float x, float y, wchar_t *str) const
  {
    text->setPosition(x, y); 
    text->setString(str); 
    target.draw(*text);
  }

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
   outtextxy(target, 5, 600, L"f - wyb�r koloru rysowania");
   outtextxy(target, 5, 615, L"b - wyb�r koloru wype�niania");
   outtextxy(target, 5, 630, L"l - rysowanie linii");

   outtextxy(target, 200, 600, L"r - rysowanie prostok�ta");
   outtextxy(target, 200, 615, L"a - rysowanie wype�nionego prostok�ta");
   outtextxy(target, 200, 630, L"c - rysowanie okr�gu");

   outtextxy(target, 470, 600, L"w - zapis do pliku");
   outtextxy(target, 470, 615, L"o - odczyt z pliku");
   outtextxy(target, 470, 630, L"esc - wyj�cie");

   outtextxy(target, 650, 615, L"Aktualne:");
   outtextxy(target, 710, 615, &flag);
   

   target.draw(*rectangle);
   target.draw(*colors_sprite);
  }

  
};

int main()
{
sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);

Menu menu;

sf::Event event;
sf::Sprite sprite;
sf::Sprite bufferSprite;
sf::RenderTexture texture;
sf::Drawable* buffer;

sf::CircleShape circle;
circle.setOutlineThickness(2.0);
circle.setFillColor(sf::Color(0,0,0,0));

sf::Color fillColor(sf::Color::Black);
sf::Color color(sf::Color::Black);

sf::VertexArray line(sf::Lines, 2);

sf::RectangleShape rectangle;
rectangle.setOutlineThickness(2.0);


bool isDrawing = false;

texture.create(800, 600);

sf::RectangleShape showMainColor(sf::Vector2f(35, 30));
sf::RectangleShape showFillColor(sf::Vector2f(35, 30));



showMainColor.setPosition(sf::Vector2f(766, 1));
showFillColor.setPosition(sf::Vector2f(766, 31));



window.setFramerateLimit(60);

while (window.isOpen())
{

  window.clear(sf::Color::Black);
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      window.close();
    }

    if (event.type == sf::Event::KeyPressed && !isDrawing)
    {
      KeyEvent(event, flag);
      if (flag == 'w')
      {
        sf::Image toFileImage(texture.getTexture().copyToImage());
        toFileImage.saveToFile("cos.jpg");
      }
      if (flag == 'o')
      {
        sf::Image image;
        sf::Texture txt;
        sf::Sprite spr;
        image.loadFromFile("cos.jpg");
        txt.loadFromImage(image);
        spr.setTexture(txt);
        texture.draw(spr);
      }
      
    }


    if (event.type == sf::Event::MouseButtonPressed)
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (flag == 'r' || flag == 'a'))
      {
        rectangle.setPosition(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y);
        buffer = &rectangle;
        isDrawing = true;
      }

      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && flag == 'c')
      {
        circle.setPosition(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y);
        buffer = &circle;
        isDrawing = true;
      }

      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && flag == 'l')
      {
       
        line[0].position = sf::Vector2f(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y);

        
        std::cout << line[0].position.y << " " << line[1].position.y << std::endl;
        
        buffer = &line;
        isDrawing = true;
      }
      else if (flag == 'f' && sf::Mouse::getPosition().x - window.getPosition().x < 764 && sf::Mouse::getPosition().y - window.getPosition().y < 60)
      {
        GetColor(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y, color);
        showMainColor.setFillColor(color);
        texture.draw(showMainColor);
      }
      else if (flag == 'b' && sf::Mouse::getPosition().x - window.getPosition().x < 764 && sf::Mouse::getPosition().y - window.getPosition().y < 60)
      {
        GetColor(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y, fillColor);
        showFillColor.setFillColor(fillColor);
        texture.draw(showFillColor);    
      }
    }

    if (event.type == sf::Event::MouseButtonReleased && isDrawing)
    {
      texture.draw(*buffer);
      isDrawing = false;
    }
  }


  //Draw BEGIN

    texture.display();


    sprite.setTexture(texture.getTexture());
    window.draw(sprite);



    if (isDrawing)
    {
      if (flag == 'r' || flag == 'a') DrawRect(rectangle, window, flag, color, fillColor);
      if (flag == 'c') DrawCircle(circle, window, color);
      if (flag == 'l') DrawLine(line, window, color, fillColor);
      
      window.draw(*buffer);

    }

    window.draw(menu);
    
    
    window.display();

   //Draw END
  }
 return 0;
}






