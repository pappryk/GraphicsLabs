#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>
/*#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>*/
#include <wx/colordlg.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame
///////////////////////////////////////////////////////////////////////////////
class MyFrame : public wxFrame 
{
private:

protected:
    wxPanel* panel;
    wxButton* starColorButton;
    wxCheckBox* bananBox;
    wxScrollBar* scrollBar;
    wxGauge* loadingGauge;
    wxButton* saveButton;
    wxTextCtrl* textBox;
    wxChoice* aChoice;
    wxImage  myImage;
    wxBitmap myBitmap;
    wxImage saveImage;
    wxString text;
    wxColourDialog* colorDialog;
    wxColour aColor;
    wxPoint smile[3];
    wxString shapeToDraw;
	wxPaintDC *MyDC;

    bool drawBanana;


    void OnExit(wxCloseEvent& e);
    void Form_Paint(wxPaintEvent& e);
    int leftSize;
    int malpkaSize; //heheszki
    int podnies;
    int niMoBanana;


    void OnClick_SaveButton(wxCommandEvent& e);
    void OnClick_ColorButton(wxCommandEvent& e);
    void OnClick_CheckBox(wxCommandEvent& e);
    void OnScroll(wxScrollEvent& e);
    void On_TextUpdated(wxCommandEvent& e);
    void OnClick_Choice(wxCommandEvent& e);
    

    enum
    {
        ID_CHECKBOX = 1001,
        ID_SCROLLBAR = 1002,
        ID_SAVEBUTTON = 1003,
        ID_COLORBUTTON = 1004,
        ID_TEXT1 = 1005,
        ID_CHOICE = 1006
    };
public:
    
    MyFrame( );
    ~MyFrame();

};
