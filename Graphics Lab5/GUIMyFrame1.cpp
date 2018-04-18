#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"
#include <iostream>
#include <sstream>

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometrie"));
 m_staticText25->SetLabel(_("Obrot X:"));
 m_staticText27->SetLabel(_("Obrot Y:"));
 m_staticText29->SetLabel(_("Obrot Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
    wxClientDC dc(WxPanel);
    dc.SetBackground(wxBrush(wxColour(255, 255, 255)));
    dc.Clear();
    double d = 2.0;
    int i;
    int w, h;
    WxPanel->GetSize(&w, &h);
    Vector4 vector;
    Vector4 vectorStop;
    double scaleX = (w - 0) / 2;
    double scaleY = (h - 0) / 2;

    Matrix4 rotateX;
    Matrix4 rotateY;
    Matrix4 rotateZ;
    Matrix4 rotate;
    Matrix4 translation;
    Matrix4 transform;
    Matrix4 scale;


    transform.data[0][0] = 1;
    transform.data[1][1] = 1;
    transform.data[2][2] = 1;    


    translation.data[0][0] = 1;
    translation.data[1][1] = 1;
    translation.data[2][2] = 1;
    translation.data[0][3] = 4.0 * (WxSB_TranslationX->GetValue() - 99) / WxSB_TranslationX->GetMax();
    translation.data[1][3] = 4.0 * (WxSB_TranslationY->GetValue() - 99) / WxSB_TranslationY->GetMax();
    translation.data[2][3] = 4.0 * (WxSB_TranslationZ->GetValue() - 99) / WxSB_TranslationZ->GetMax() ;
    //translation.data[0][3] = 0;
    //translation.data[1][3] = 0;
    //translation.data[2][3] = 0;

    rotateX.data[0][0] = 1;
    rotateX.data[1][1] = cos(1.0 * WxSB_RotateX->GetValue() / WxSB_RotateX->GetMax() * 2 * M_PI);
    rotateX.data[1][2] = -sin(1.0 * WxSB_RotateX->GetValue() / WxSB_RotateX->GetMax() * 2 * M_PI);
    rotateX.data[2][1] = sin(1.0 * WxSB_RotateX->GetValue() / WxSB_RotateX->GetMax() * 2 * M_PI);
    rotateX.data[2][2] = cos(1.0 * WxSB_RotateX->GetValue() / WxSB_RotateX->GetMax() * 2 * M_PI);    


    rotateY.data[1][1] = 1;
    rotateY.data[0][0] = cos(1.0 * WxSB_RotateY->GetValue() / WxSB_RotateY->GetMax() * 2 * M_PI);
    rotateY.data[2][0] = -sin(1.0 * WxSB_RotateY->GetValue() / WxSB_RotateY->GetMax() * 2 * M_PI);
    rotateY.data[0][2] = sin(1.0 * WxSB_RotateY->GetValue() / WxSB_RotateY->GetMax() * 2 * M_PI);
    rotateY.data[2][2] = cos(1.0 * WxSB_RotateY->GetValue() / WxSB_RotateY->GetMax() * 2 * M_PI);    

    rotateZ.data[2][2] = 1;
    rotateZ.data[0][0] = cos(1.0 * WxSB_RotateZ->GetValue() / WxSB_RotateZ->GetMax() * 2 * M_PI);
    rotateZ.data[0][1] = -sin(1.0 * WxSB_RotateZ->GetValue() / WxSB_RotateZ->GetMax() * 2 * M_PI);
    rotateZ.data[1][0] = sin(1.0 * WxSB_RotateZ->GetValue() / WxSB_RotateZ->GetMax() * 2 * M_PI);
    rotateZ.data[1][1] = cos(1.0 * WxSB_RotateZ->GetValue() / WxSB_RotateZ->GetMax() * 2 * M_PI); 


    scale.data[0][0] = 2.0 * WxSB_ScaleX->GetValue() / WxSB_ScaleX->GetMax();
    scale.data[1][1] = 2.0 * WxSB_ScaleY->GetValue() / WxSB_ScaleY->GetMax(); 
    scale.data[2][2] = 2.0 * WxSB_ScaleZ->GetValue() / WxSB_ScaleZ->GetMax();
    //scale.data[0][0] = 1;
    //scale.data[1][1] = 1;
    //scale.data[2][2] = 1;
    
    
    transform = transform * translation;
    transform = transform * scale;        
    transform = transform * rotateX;
    transform = transform * rotateY;
    transform = transform * rotateZ;
    
    

    for (i = 0; i < data.size(); i++)
    {
        vector.Set(data[i].begin.x , data[i].begin.y, data[i].begin.z);
        vectorStop.Set(data[i].end.x , data[i].end.y, data[i].end.z);

        vector = transform * vector;
        vectorStop = transform * vectorStop;
        

        dc.SetPen(wxPen(wxColour(data[i].color.R, data[i].color.G, data[i].color.B)));      
        dc.DrawLine(w/2 + scaleX*vector.GetX()/(1 + vector.GetZ()/d),
                    h/2 + scaleY*vector.GetY()/(1 + vector.GetZ()/d),
                    w/2 + scaleX*vectorStop.GetX()/(1 + vectorStop.GetZ()/d),
                    h/2 + scaleY*vectorStop.GetY()/(1 + vectorStop.GetZ()/d));
    }
}