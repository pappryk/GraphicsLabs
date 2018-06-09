#include "MyFrame.h"

void MyFrame::OnExit(wxCloseEvent& e)
{
    Destroy();
}



MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Niby Malpka")
{
	this->SetSizeHints( wxSize( 800, 600 ), wxDefaultSize );
	leftSize = 110;
	malpkaSize = 50;
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* leftSizer;
	leftSizer = new wxBoxSizer( wxVERTICAL );
	
	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	leftSizer->Add( panel, 1, wxEXPAND | wxALL, 5 );
	
	
	mainSizer->Add( leftSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* rightSizer;
	rightSizer = new wxBoxSizer( wxVERTICAL );
	
	saveButton = new wxButton( this, ID_SAVEBUTTON, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( saveButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bananBox = new wxCheckBox( this, ID_CHECKBOX, wxT("Banan?"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( bananBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	scrollBar = new wxScrollBar( this, ID_SCROLLBAR, wxDefaultPosition, wxSize( 200,-1 ), wxSB_HORIZONTAL );
	//scrollBar->SetMinSize( wxSize( -1,-1 ) );
	scrollBar->SetScrollbar(0, 5, 105, 5);
	
	rightSizer->Add( scrollBar, 0, wxALL, 5 );
	
	loadingGauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( 200,-1 ), wxGA_HORIZONTAL );
	loadingGauge->SetValue( 0 ); 
	rightSizer->Add( loadingGauge, 0, wxALL, 5 );
	
	starColorButton = new wxButton( this, ID_COLORBUTTON, wxT("Kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( starColorButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	textBox = new wxTextCtrl( this, wxID_ANY, "Difjult", wxDefaultPosition, wxDefaultSize, 0 );
	textBox->SetMinSize( wxSize( 150,-1 ) );
	
	rightSizer->Add( textBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString choices;
	choices.Add(wxString("Gwiazdka"));
	choices.Add(wxString("Ksiezyc"));
	choices.Add(wxString("Sloneczko"));
	aChoice = new wxChoice( this, ID_CHOICE, wxDefaultPosition, wxDefaultSize, choices, 0 );
	aChoice->SetSelection( 0 );
	rightSizer->Add( aChoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	text = "Difjult";
	
	
	mainSizer->Add( rightSizer, 0, wxEXPAND, 5 );
	myImage.AddHandler(new wxPNGHandler);
	//saveImage.AddHandler(new wxPNGHandler);
	saveImage.AddHandler(new wxJPEGHandler);
	myImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
   	myBitmap = wxBitmap(myImage);

	//leftSizer->Add( text1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );



	//// INITIALIZE VARIABLES
	drawBanana = false;
	podnies = 0;
	niMoBanana = 0;
	colorDialog = new wxColourDialog(this, NULL);
	aColor = wxColour(100, 100, 100);
	shapeToDraw = "Gwiazdka";
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	this->Centre( wxBOTH );



	//// BIND
	Bind(wxEVT_PAINT, &MyFrame::Form_Paint, this);
	Bind(wxEVT_CHECKBOX, &MyFrame::OnClick_CheckBox, this, ID_CHECKBOX);
	scrollBar->Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::OnScroll, this);
	textBox->Bind(wxEVT_TEXT, &MyFrame::On_TextUpdated, this, ID_TEXT1);
	Bind(wxEVT_COMMAND_TEXT_UPDATED, &MyFrame::On_TextUpdated, this);
	Bind(wxEVT_BUTTON, &MyFrame::OnClick_ColorButton, this, ID_COLORBUTTON);
	Bind(wxEVT_BUTTON, &MyFrame::OnClick_SaveButton, this, ID_SAVEBUTTON);
	Bind(wxEVT_COMMAND_CHOICE_SELECTED, &MyFrame::OnClick_Choice, this, ID_CHOICE);
}

MyFrame::~MyFrame()
{
}

void MyFrame::Form_Paint(wxPaintEvent& e)
{
	MyDC = new wxPaintDC(panel);

	MyDC->SetBackground(wxBrush(wxColour(255, 255, 255), wxSOLID));
	MyDC->Clear();

	smile[0] = wxPoint(wxWindow::GetSize().x / 2 - leftSize - 15, wxWindow::GetSize().y / 2 - 20 - 40 + 20);
	smile[1] = wxPoint(wxWindow::GetSize().x / 2 - leftSize + 15 - 15, wxWindow::GetSize().y / 2 - 20 - 40 - 10 + 20 + niMoBanana);
	smile[2] = wxPoint(wxWindow::GetSize().x / 2 - leftSize + 30 - 15, wxWindow::GetSize().y / 2 - 20 - 40 + 20);	

	/// banana
	if (drawBanana)	MyDC->DrawBitmap(myBitmap, wxWindow::GetSize().x / 2 - leftSize - 75 - 30, wxWindow::GetSize().y / 2 + 40 - 30 - podnies / 2);
	
	MyDC->SetBrush(wxBrush(wxColour(100, 100, 100), wxTRANSPARENT));	
	/// legs
	MyDC->DrawLine(wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2 + 100, wxWindow::GetSize().x / 2 + 50 - leftSize, wxWindow::GetSize().y / 2 + 150);		
	MyDC->DrawLine(wxWindow::GetSize().x / 2 - leftSize - 50, wxWindow::GetSize().y / 2 + 150, wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2 + 100);	
	/// torso	
	MyDC->DrawLine(wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2 - 20, wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2 + 100);
	/// arms
	MyDC->DrawLine(wxWindow::GetSize().x / 2 - leftSize - 75, wxWindow::GetSize().y / 2 + 40 - podnies / 2, wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2);
	MyDC->DrawLine(wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2, wxWindow::GetSize().x / 2 - leftSize + 75, wxWindow::GetSize().y / 2 + 40);
	/// head
	MyDC->DrawCircle(wxPoint(wxWindow::GetSize().x / 2 - leftSize, wxWindow::GetSize().y / 2 - 20 - 40), 40);
	/// eyes
	MyDC->DrawCircle(wxPoint(wxWindow::GetSize().x / 2 - leftSize - 15, wxWindow::GetSize().y / 2 - 20 - 40 - 5), 8);
	MyDC->DrawCircle(wxPoint(wxWindow::GetSize().x / 2 - leftSize + 15, wxWindow::GetSize().y / 2 - 20 - 40 - 5), 8);
	if (shapeToDraw == "Gwiazdka") 
	{
		MyDC->SetPen(wxPen(aColor, 1, wxSOLID));
		MyDC->SetBrush(wxBrush(aColor, wxSOLID));	
		MyDC->DrawCircle(100, 100, 50);
	}
	else if (shapeToDraw == "Sloneczko")
	{
		MyDC->SetPen(wxPen(wxColour(255, 255, 255), 1, wxTRANSPARENT));
		MyDC->SetBrush(wxBrush(wxColor(255, 255, 0), wxSOLID));			
		MyDC->DrawCircle(100, 100, 50);
	}
	else
	{
		MyDC->SetBrush(wxBrush(wxColor(100, 100, 100), wxSOLID));			
		MyDC->DrawCircle(100, 100, 50);
		MyDC->SetPen(wxPen(wxColour(100, 100, 100), 1, wxTRANSPARENT));
		MyDC->SetBrush(wxBrush(wxColor(255, 255, 255), wxSOLID));
		MyDC->DrawCircle(80, 80, 50);		
	}
	MyDC->SetPen(wxPen(wxColour(0, 0, 0), 1, wxSOLID));	
	MyDC->DrawSpline(3, smile);

	MyDC->DrawText(text, 100, 350);
	MyDC->DrawRotatedText(text, wxWindow::GetSize().x / 2 - leftSize + 110, wxWindow::GetSize().y / 2 + 100, 90);

	delete (MyDC);
}



void MyFrame::OnClick_CheckBox(wxCommandEvent& e)
{
	if (bananBox->IsChecked())
	{
		drawBanana = true;
		niMoBanana = 15;
	}
	else
	{
		drawBanana = false;
		niMoBanana = 0;
	}
}



void MyFrame::OnScroll(wxScrollEvent& e)
{
	this->podnies = scrollBar->GetThumbPosition();
	loadingGauge->SetValue(scrollBar->GetThumbPosition());
	//text1->SetLabel(wxString::Format("%d", scrollBar->GetThumbPosition()));
}




void MyFrame::OnClick_ColorButton(wxCommandEvent& e)
{
	colorDialog->ShowModal();
	aColor = colorDialog->GetColourData().GetColour();
}

void MyFrame::On_TextUpdated(wxCommandEvent& e)
{
	text = textBox->GetValue();
	shapeToDraw = aChoice->GetString(aChoice->GetSelection());
	this->Refresh();	
}


void MyFrame::OnClick_Choice(wxCommandEvent& e)
{
	shapeToDraw = aChoice->GetString(aChoice->GetSelection());
	this->Refresh();	
}


void MyFrame::OnClick_SaveButton(wxCommandEvent& e)
{
	int x, y;
	wxClientDC clientDC(panel);
	wxMemoryDC memoryDC;
	panel->GetSize(&x, &y);
	wxBitmap *bitmap = new wxBitmap(x, y);
	memoryDC.SelectObject(*bitmap);	
	memoryDC.Blit(0, 0, x, y, &clientDC, 0, 0, wxCOPY, true);
	saveImage = bitmap->ConvertToImage();
	saveImage.SaveFile("obraz.jpg", wxBITMAP_TYPE_JPEG);
}