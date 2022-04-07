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
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/tglbtn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/statbmp.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>

///////////////////////////////////////////////////////////////////////////


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
		wxButton* saveLayoutButton;
		wxButton* reloadLayoutButton;
		wxButton* resetLayoutButton;
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
		virtual void OnSaveLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReloadLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioInDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeIn( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnAudioOutDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeOut( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnVideoInChanged( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MonitorFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Monitor - Debug"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 2400,1000 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MonitorFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TopVideoFrameGen
///////////////////////////////////////////////////////////////////////////////
class TopVideoFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxPanel* TopVideoPanel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		TopVideoFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Video"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,512 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopVideoFrameGen();
	
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
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTextInClearButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextOutClearButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TopTextFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22-Text"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,650 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopTextFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class WhiteboardFrameGen
///////////////////////////////////////////////////////////////////////////////
class WhiteboardFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxBitmapButton* WhiteButton;
		wxBitmapButton* BlackButton;
		wxBitmapButton* RedButton;
		wxBitmapButton* GreenButton;
		wxBitmapButton* BlueButton;
		wxBitmapButton* YellowButton;
		wxBitmapButton* CyanButton;
		wxBitmapButton* MagentaButton;
		wxButton* ClearButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnWhiteButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBlackButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRedButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGreenButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBlueButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnYellowButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCyanButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMagentaButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnWhiteboardClearButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* WhiteboardHorizPanel;
		
		WhiteboardFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS - Whiteboard"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,500 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~WhiteboardFrameGen();
	
};

#endif //__SRS22UIGEN_H__
