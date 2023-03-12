///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TopFrame
///////////////////////////////////////////////////////////////////////////////
class TopFrame : public wxFrame 
{
	private:
	
	protected:
		wxButton* m_button1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnMyButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TopFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1086,701 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopFrame();
	
};

#endif //__NONAME_H__
