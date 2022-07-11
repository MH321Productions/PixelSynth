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
/// Class ssynthFrame
///////////////////////////////////////////////////////////////////////////////
class ssynthFrame : public wxFrame
{
	private:

	protected:
		wxPanel* panelFreq;
		wxSlider* sliderFreq;
		wxStaticText* lblFreq;
		wxPanel* panelSynth;
		wxBitmapButton* btnSine;
		wxBitmapButton* btnSquare;
		wxBitmapButton* btnLinear;
		wxBitmapButton* btnSaw;
		wxBitmapButton* btnNoise;

		// Virtual event handlers, override them in your derived class
		virtual void onIdle( wxIdleEvent& event ) { event.Skip(); }


	public:

		ssynthFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PixelSynth - Simple Synth"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~ssynthFrame();

};

