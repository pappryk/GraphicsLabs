#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"
#include <math.h>

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg = std::move(c);
    x_step = 200;
    translation = new Matrix;
    translation_2 = new Matrix;
    translation_back = new Matrix;
    rotation = new Matrix;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                translation->data[i][j] = 1;
                translation_2->data[i][j] = 1;
                translation_back->data[i][j] = 1;
                rotation->data[i][j] = 1; 
            }  
            else
            {
                translation->data[i][j] = 0;
                translation_2->data[i][j] = 0;
                translation_back->data[i][j] = 0;
                rotation->data[i][j] = 0;
            }           
        }
    
    

}

void ChartClass::Set_Range()
{
    double xmin = 9999.9, xmax = -9999.9 , ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin = cfg->Get_x_start();
    xmax = cfg->Get_x_stop();

    step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
    x = cfg->Get_x_start();

    for (i=0 ;i <= x_step; i++)
    {
        y = GetFunctionValue(x);
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x)
{
    if (cfg->Get_F_type() == 1) return x * x;
    if (cfg->Get_F_type() == 2) return 0.5*exp(4*x - 3*x*x);
    return x + sin(x * 4.0);
}




void ChartClass::Draw(wxDC *dc, int w, int h)
{
    dc->SetBackground(wxBrush(wxColour(255, 255, 255)));
    dc->Clear();
    dc->SetPen(wxPen(wxColour(255, 0, 0)));
    dc->DrawRectangle(10, 10, w - 20, h - 20);


    Vector vector;
    Vector horizontalLine1;
    Vector horizontalLine2;    
    Vector verticalLine1;
    Vector verticalLine2;
    
    
    double x = cfg->Get_x_start();
    double step = abs(cfg->Get_x_stop() - cfg->Get_x_start()) / x_step;
    double scaleX = (w - 0) / abs((cfg->Get_x1() - cfg->Get_x0()));
    double scaleY = (h - 0) / abs((cfg->Get_y1() - cfg->Get_y0()));

    translation->data[0][2] = cfg->Get_dX();
    translation->data[1][2] = cfg->Get_dY();
    translation_back->data[0][2] = -cfg->Get_dX();
    translation_back->data[1][2] = -cfg->Get_dY();
    

    translation_2->data[0][0] = 1;
    translation_2->data[1][1] = 1;
    translation_2->data[0][2] = -cfg->Get_x0() * scaleX;
    translation_2->data[1][2] = -cfg->Get_y0() * scaleY;


    rotation->data[0][0] = cos(cfg->Get_Alpha() / 180 * M_PI);
    rotation->data[0][1] = -sin(cfg->Get_Alpha() / 180 * M_PI);
    rotation->data[1][0] = sin(cfg->Get_Alpha() / 180 * M_PI);
    rotation->data[1][1] = cos(cfg->Get_Alpha() / 180 * M_PI);
    

    horizontalLine1.Set(scaleX * cfg->Get_x_start(), 0);
    horizontalLine2.Set(scaleX * cfg->Get_x_stop(), 0);

    verticalLine1.Set(0, -scaleY * Get_Y_min());
    verticalLine2.Set(0, -scaleY * Get_Y_max());


    if(cfg->RotateScreenCenter())
    {
        horizontalLine1 = (*translation) * horizontalLine1;
        horizontalLine2 = (*translation) * horizontalLine2;
        verticalLine1 = (*translation) * verticalLine1;
        verticalLine2 = (*translation) * verticalLine2;
    }

    horizontalLine1 = (*rotation) * horizontalLine1;
    horizontalLine2 = (*rotation) * horizontalLine2;
    horizontalLine1 = (*translation_2) * horizontalLine1;
    horizontalLine2 = (*translation_2) * horizontalLine2;
    

    verticalLine1 = (*rotation) * verticalLine1;
    verticalLine2 = (*rotation) * verticalLine2;
    verticalLine1 = (*translation_2) * verticalLine1;
    verticalLine2 = (*translation_2) * verticalLine2;



    if (!cfg->RotateScreenCenter())
    {
        horizontalLine1 = (*translation) * horizontalLine1;
        horizontalLine2 = (*translation) * horizontalLine2;
        verticalLine1 = (*translation) * verticalLine1;
        verticalLine2 = (*translation) * verticalLine2;
    }

    
    
    

    
    for (int i = 0; i < x_step; i++)
        {
            
            vector.Set(x * scaleX, -1.0 * GetFunctionValue(x) * scaleY);

            if (cfg->RotateScreenCenter())
            {
                vector = (*translation) * vector;
            }
            vector = (*rotation) * vector;
            vector = (*translation_2) * vector;

            if (!cfg->RotateScreenCenter())
            {
                vector = (*translation) * vector;
            }

            chart[i] = wxPoint(vector.GetX(), vector.GetY());
            x += step;
        }
    dc->SetPen(wxPen(wxColour(0, 0, 255)));    

    dc->SetClippingRegion(wxRect(11, 11, w - 22, h - 22));

    dc->DrawLine(horizontalLine1.GetX(), horizontalLine1.GetY(), horizontalLine2.GetX(), horizontalLine2.GetY());
    dc->DrawLine(verticalLine1.GetX(), verticalLine1.GetY(), verticalLine2.GetX(), verticalLine2.GetY());

    dc->SetPen(wxPen(wxColour(0, 255, 0)));
    dc->DrawSpline(x_step, chart);
    
}


double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

