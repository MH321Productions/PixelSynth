///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/slider.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SSynthFrame
///////////////////////////////////////////////////////////////////////////////
class SSynthFrame : public wxFrame
{
	private:

	protected:
		wxPanel* panelFreq;
		wxSlider* sliderFreq;
		wxStaticText* lblFreqText;
		wxStaticText* lblFreq;
		wxStaticText* lblDevText;
		wxChoice* cmbDevice;
		wxPanel* panelSynth;
		wxBitmapButton* btnSine;
		wxBitmapButton* btnSquare;
		wxBitmapButton* btnTriangle;
		wxBitmapButton* btnSaw;
		wxBitmapButton* btnNoise;

		// Virtual event handlers, override them in your derived class
		virtual void onIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void onFreq( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSine( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSquare( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTriangle( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSaw( wxCommandEvent& event ) { event.Skip(); }
		virtual void onNoise( wxCommandEvent& event ) { event.Skip(); }


	public:

		SSynthFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PixelSynth - Simple Synth"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~SSynthFrame();

};

