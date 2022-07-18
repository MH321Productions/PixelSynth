///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SSynth.h"

///////////////////////////////////////////////////////////////////////////

SSynthFrame::SSynthFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 620,300 ), wxSize( 620,300 ) );

	wxBoxSizer* sizerMain;
	sizerMain = new wxBoxSizer( wxVERTICAL );

	panelFreq = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerFreq;
	sizerFreq = new wxBoxSizer( wxVERTICAL );

	sliderFreq = new wxSlider( panelFreq, wxID_ANY, 440, 1, 2000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sizerFreq->Add( sliderFreq, 0, wxALL|wxEXPAND, 5 );

	wxFlexGridSizer* sizerFreqDevice;
	sizerFreqDevice = new wxFlexGridSizer( 1, 4, 0, 0 );
	sizerFreqDevice->AddGrowableCol( 1 );
	sizerFreqDevice->AddGrowableCol( 3 );
	sizerFreqDevice->SetFlexibleDirection( wxBOTH );
	sizerFreqDevice->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	lblFreqText = new wxStaticText( panelFreq, wxID_ANY, wxT("Frequency:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	lblFreqText->Wrap( -1 );
	sizerFreqDevice->Add( lblFreqText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	lblFreq = new wxStaticText( panelFreq, wxID_ANY, wxT("440 Hz"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
	lblFreq->Wrap( -1 );
	sizerFreqDevice->Add( lblFreq, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	lblDevText = new wxStaticText( panelFreq, wxID_ANY, wxT("Audio device:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblDevText->Wrap( -1 );
	sizerFreqDevice->Add( lblDevText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	wxArrayString cmbDeviceChoices;
	cmbDevice = new wxChoice( panelFreq, wxID_ANY, wxDefaultPosition, wxDefaultSize, cmbDeviceChoices, 0 );
	cmbDevice->SetSelection( 0 );
	cmbDevice->SetToolTip( wxT("Select the audio output device") );

	sizerFreqDevice->Add( cmbDevice, 0, wxALL|wxEXPAND, 5 );


	sizerFreq->Add( sizerFreqDevice, 1, wxEXPAND, 5 );


	panelFreq->SetSizer( sizerFreq );
	panelFreq->Layout();
	sizerFreq->Fit( panelFreq );
	sizerMain->Add( panelFreq, 1, wxEXPAND | wxALL, 5 );

	panelSynth = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 1, 5, 0, 0 );

	btnSine = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	btnSine->SetToolTip( wxT("Sine Wave") );

	gSizer1->Add( btnSine, 0, wxALL|wxEXPAND, 5 );

	btnSquare = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	btnSquare->SetToolTip( wxT("Square Wave") );

	gSizer1->Add( btnSquare, 0, wxALL|wxEXPAND, 5 );

	btnTriangle = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	btnTriangle->SetToolTip( wxT("Triangle Wave") );

	gSizer1->Add( btnTriangle, 0, wxALL|wxEXPAND, 5 );

	btnSaw = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	btnSaw->SetToolTip( wxT("Sawtooth Wave") );

	gSizer1->Add( btnSaw, 0, wxALL|wxEXPAND, 5 );

	btnNoise = new wxBitmapButton( panelSynth, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|0 );
	btnNoise->SetToolTip( wxT("Noise") );

	gSizer1->Add( btnNoise, 0, wxALL|wxEXPAND, 5 );


	panelSynth->SetSizer( gSizer1 );
	panelSynth->Layout();
	gSizer1->Fit( panelSynth );
	sizerMain->Add( panelSynth, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( sizerMain );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( SSynthFrame::onIdle ) );
	sliderFreq->Connect( wxEVT_SLIDER, wxCommandEventHandler( SSynthFrame::onFreq ), NULL, this );
	btnSine->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSine ), NULL, this );
	btnSquare->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSquare ), NULL, this );
	btnTriangle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onTriangle ), NULL, this );
	btnSaw->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSaw ), NULL, this );
	btnNoise->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onNoise ), NULL, this );
}

SSynthFrame::~SSynthFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( SSynthFrame::onIdle ) );
	sliderFreq->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( SSynthFrame::onFreq ), NULL, this );
	btnSine->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSine ), NULL, this );
	btnSquare->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSquare ), NULL, this );
	btnTriangle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onTriangle ), NULL, this );
	btnSaw->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onSaw ), NULL, this );
	btnNoise->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SSynthFrame::onNoise ), NULL, this );

}
