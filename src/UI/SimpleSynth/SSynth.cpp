///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SSynth.h"

///////////////////////////////////////////////////////////////////////////

ssynthFrame::ssynthFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* sizerMain;
	sizerMain = new wxBoxSizer( wxVERTICAL );

	panelFreq = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerFreq;
	sizerFreq = new wxBoxSizer( wxVERTICAL );

	sliderFreq = new wxSlider( panelFreq, wxID_ANY, 440, 1, 10000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sizerFreq->Add( sliderFreq, 0, wxALL|wxEXPAND, 5 );

	lblFreq = new wxStaticText( panelFreq, wxID_ANY, wxT("Frequenz: 440 Hz"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	lblFreq->Wrap( -1 );
	sizerFreq->Add( lblFreq, 0, wxALL|wxEXPAND, 5 );


	panelFreq->SetSizer( sizerFreq );
	panelFreq->Layout();
	sizerFreq->Fit( panelFreq );
	sizerMain->Add( panelFreq, 1, wxEXPAND | wxALL, 5 );

	panelSynth = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 1, 5, 0, 0 );

	btnSine = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	gSizer1->Add( btnSine, 0, wxALL|wxEXPAND, 5 );

	btnSquare = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	gSizer1->Add( btnSquare, 0, wxALL|wxEXPAND, 5 );

	btnLinear = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	gSizer1->Add( btnLinear, 0, wxALL|wxEXPAND, 5 );

	btnSaw = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	gSizer1->Add( btnSaw, 0, wxALL|wxEXPAND, 5 );

	btnNoise = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	gSizer1->Add( btnNoise, 0, wxALL|wxEXPAND, 5 );


	panelSynth->SetSizer( gSizer1 );
	panelSynth->Layout();
	gSizer1->Fit( panelSynth );
	sizerMain->Add( panelSynth, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( sizerMain );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( ssynthFrame::onIdle ) );
}

ssynthFrame::~ssynthFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( ssynthFrame::onIdle ) );

}
