#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasnosc"));
 m_b_threshold->SetLabel(_(L"Prog 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 // TO DO: Konwersja do skali szarosci
    Img_Cpy = Img_Org.ConvertToGreyscale();
    Repaint(true);         
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
 // TO DO: Rozmywanie obrazu (blur)
    Img_Cpy = Img_Org.Blur(5);
    Repaint(true);     
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
 // TO DO: Odbicie lustrzane
    Img_Cpy = Img_Org;
    Img_Cpy = Img_Cpy.Mirror();
    Repaint(true); 
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
 // TO DO: Zamiana kolorow 
    m_scrolledWindow->ClearBackground();    
    Img_Cpy=Img_Org.Copy();
    Img_Cpy.Replace(254,0,0,0,0,255);
    Repaint(true);    
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
 // TO DO: Zmiana rozmiarow do 320x240
    m_scrolledWindow->ClearBackground();     
    Img_Cpy = Img_Org; 
    Img_Cpy.Rescale(320, 240);
    Repaint(true);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
 // TO DO: Obrot o 30 stopni
    m_scrolledWindow->ClearBackground();
    Img_Cpy = Img_Org.Rotate(30.0/180 * M_PI, wxPoint(Img_Cpy.GetWidth(), Img_Cpy.GetHeight()));
    Repaint(true);    
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
 // TO DO: Przesuniecie Hue o 180 stopni
    m_scrolledWindow->ClearBackground();     
    Img_Cpy = Img_Org;
    Img_Cpy.RotateHue(0.5);
    Repaint(true);
    
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
 // TO DO: Ustawienie maski obrazu
    m_scrolledWindow->ClearBackground();     
    Img_Cpy = Img_Org;
    Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
    Repaint(true);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint(true);
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint(true);
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
 // TO DO: Pionowa maska Prewitta
    Img_Cpy = Img_Org;
    int r, g, b;
    for(int i = 1; i < Img_Cpy.GetWidth() - 1; i++)
    {
        for(int j = 1; j < Img_Cpy.GetHeight() - 1; j++)
        {
            r = Img_Org.GetRed(i - 1, j - 1) + Img_Org.GetRed(i, j - 1) + Img_Org.GetRed(i, j - 1) -
                Img_Org.GetRed(i - 1, j + 1) - Img_Org.GetRed(i, j + 1) - Img_Org.GetRed(i + 1, j + 1);

            g = Img_Org.GetGreen(i - 1, j - 1) + Img_Org.GetGreen(i, j - 1) + Img_Org.GetGreen(i, j - 1) -
                Img_Org.GetGreen(i - 1, j + 1) - Img_Org.GetGreen(i, j + 1) - Img_Org.GetGreen(i + 1, j + 1);

            b = Img_Org.GetBlue(i - 1, j - 1) + Img_Org.GetBlue(i, j - 1) + Img_Org.GetBlue(i, j - 1) -
                Img_Org.GetBlue(i - 1, j + 1) - Img_Org.GetBlue(i, j + 1) - Img_Org.GetBlue(i + 1, j + 1);
            
            if (r > 255) { r = 255; } else if (r < 0) { r = 0; }
            if (g > 255) { g = 255; } else if (g < 0) { g = 0; }
            if (b > 255) { b = 255; } else if (b < 0) { b = 0; }

            Img_Cpy.SetRGB(i, j, r, g, b);
    }}
    
    Repaint(true);
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
    Img_Cpy = Img_Org.Copy();
    unsigned char* data = Img_Cpy.GetData();
    for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++)
    {
        if (data[i] > 128){data[i] = 255;}
        else { data[i] = 0;}
    }
}


void GUIMyFrame1::Contrast(int val)
{
 // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
    double a;
    double value = val * 255.0 / 100.0;
    if (value <= 0)
    {
        a = 1.0 + value / 255.0;
    }
    else
    {
        a = 255.0 / pow(2, log2(256.0 - value));
    }
    Img_Cpy = Img_Org.Copy();

    unsigned char* data = Img_Cpy.GetData();
    for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++)
    {
        if (a * (data[i] - 127.0) + 127.0 < 0)
        {
            data[i] = 0;
        }
        else if (a * (data[i] - 127.0) + 127.0 > 255)
        {
            data[i] = 255;
        }
        else
        {
            data[i] =  a * (data[i] - 127) + 127;            
        }
    }
}


void GUIMyFrame1::Repaint(bool clear)
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 if (clear) dc.Clear();
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
 // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    Img_Cpy = Img_Org.Copy();
    unsigned char* data = Img_Cpy.GetData();
    for (int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; i++)
    {
        if (data[i] + value > 255) { data[i] = 255; }
        else if (data[i] + value < 0) { data[i] = 0; }
        else {data[i] += value; }
    }
}