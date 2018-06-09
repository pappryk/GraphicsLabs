#include "CircleHSV.h"

CircleHSV::CircleHSV(sf::Vector2f vec, int radius) : Circle(vec, radius)
{
    
}

void CircleHSV::ChangeColor(float scaleColor)
{
    for (int i = 0; i < px; i++)
    {
        for (int j = 0; j < radius; j++)
        {
            image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, hsv(360 - 360 * i / px, 1.0 * j / radius, scaleColor));
        }
    }
    texture.loadFromImage(image);
    //texture.update(pixels);
    this->setTexture(&texture);
    //sprite.setTexture(texture);
}



sf::Color hsv(int hue, float sat, float val)
{
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.0) sat = 0.0;
  if(sat>1.0) sat = 1.0;

  if(val<0.0) val = 0.0;
  if(val>1.0) val = 1.0;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.0-sat);
  float q = val*(1.0-sat*f);
  float t = val*(1.0-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(val*255, t*255, p*255);
    case 1: return sf::Color(q*255, val*255, p*255);
    case 2: return sf::Color(p*255, val*255, t*255);
    case 3: return sf::Color(p*255, q*255, val*255);
    case 4: return sf::Color(t*255, p*255, val*255);
    case 5: return sf::Color(val*255, p*255, q*255);
  }
}