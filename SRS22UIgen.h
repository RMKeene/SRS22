///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SRS22UIGEN_H__
#define __SRS22UIGEN_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/tglbtn.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/statbmp.h>
#include <wx/richtext/richtextctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TopVideoFrameGen
///////////////////////////////////////////////////////////////////////////////
class TopVideoFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxPanel* TopVideoPanel;
	
	public:
		
		TopVideoFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Video"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 620,474 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopVideoFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MonitorFrameGen
///////////////////////////////////////////////////////////////////////////////
class MonitorFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* MonitorFrameMenuBar;
		wxMenu* m_menu5;
		wxToggleButton* RunButton;
		wxButton* MonitorStepButton;
		wxStaticText* m_staticText91;
		wxChoice* AudioInChoiceDropbox;
		wxStaticText* m_staticText181;
		wxSlider* AudioInVolume;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText9;
		wxChoice* AudioOutChoiceDropbox;
		wxStaticText* m_staticText18;
		wxSlider* AudioOutVolume;
		wxStaticText* m_staticText911;
		wxChoice* VideoInChoiceDropbox;
		wxStaticBitmap* AudioInFFTBitmapWidget;
		wxStaticBitmap* AudioOutFFTBitmapWidget;
		wxStaticText* MonitorStatisticsLine1;
		wxStaticText* MonitorStatisticsLine2;
		wxStaticText* MonitorStatisticsLine3;
		wxStaticText* MonitorStatisticsLine4;
		wxRichTextCtrl* LogRichText;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRunToggleButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStep( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioInDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeIn( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnAudioOutDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeOut( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnVideoInChanged( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MonitorFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Monitor - Debug"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1189,739 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MonitorFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TopTextFrameGen
///////////////////////////////////////////////////////////////////////////////
class TopTextFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxButton* TextInClearButton;
		wxRichTextCtrl* TextInRichText;
		wxButton* TextOutClearButton1;
		wxRichTextCtrl* TextOutRichText;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTextInClearButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextOutClearButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TopTextFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22-Text"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1006,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopTextFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SRSWhiteboardGen
///////////////////////////////////////////////////////////////////////////////
class SRSWhiteboardGen : public wxFrame 
{
	private:
	
	protected:
	
	public:
		
		SRSWhiteboardGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS - Whiteboard"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 799,625 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~SRSWhiteboardGen();
	
};

#endif //__SRS22UIGEN_H__
