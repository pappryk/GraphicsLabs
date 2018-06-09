#include "CircleHSL.h"

CircleHSL::CircleHSL(sf::Vector2f vec, int radius) : Circle(vec, radius)
{
    
}

void CircleHSL::ChangeColor(float scaleColor)
{
    for (int i = 0; i < px; i++)
    {
        for (int j = 0; j < radius; j++)
        {
            if (scaleColor > 1.0) scaleColor = 1.0;
            if (scaleColor < 0.0) scaleColor = 0.0;
            image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, hsl(1.0 - 1.0 * i / px, 1.0 * j / radius, scaleColor));
            //image.setPixel(radius + cos(i * 2 * M_PI / px) * j, radius + sin(i * 2 * M_PI / px) * j, sf::Color(255 * j / radius, 255 - 255 *i / px, 255 , 255));
            
        }
    }
    texture.loadFromImage(image);
    //texture.update(pixels);
    this->setTexture(&texture);
    //sprite.setTexture(texture);
}



sf::Color hsl(float H, float S, float L)
{
    int R, G, B;
    float var_1, var_2;
    if ( S == 0 )
    {

        R = L * 255;
        G = L * 255;
        B = L * 255;
    }
    else
    {
        if ( L < 0.5 ) { var_2 = L * ( 1 + S ); }
        else           { var_2 = ( L + S ) - ( S * L ); }

        var_1 = 2 * L - var_2;

        R = 255 * Hue_2_RGB( var_1, var_2, H + ( 1 / 3 ) );
        G = 255 * Hue_2_RGB( var_1, var_2, H );
        B = 255 * Hue_2_RGB( var_1, var_2, H - ( 1 / 3 ) );
    }
    return sf::Color(R, G, B);
}

float Hue_2_RGB(float v1, float v2, float vH )             //Function Hue_2_RGB
{
   if ( vH < 0 ) vH += 1;
   if( vH > 1 ) vH -= 1;
   if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
   if ( ( 2 * vH ) < 1 ) return ( v2 );
   if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2 / 3 ) - vH ) * 6 );
   return v1;

}