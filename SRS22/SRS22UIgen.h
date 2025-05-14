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
#include <wx/tglbtn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/bmpbuttn.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MonitorFrameGen
///////////////////////////////////////////////////////////////////////////////
class MonitorFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxToggleButton* RunButton;
		wxButton* MonitorStepButton;
		wxButton* ContinueButton;
		wxStaticText* TickCountText;
		wxStaticText* TicksPerSecondText;
		wxButton* saveLayoutButton;
		wxButton* reloadLayoutButton;
		wxButton* resetLayoutButton;
		wxButton* TestAButton;
		wxButton* TestBButton;
		wxButton* GoodButton;
		wxButton* BadButton;
		wxStaticText* overallGoodnessLabel;
		wxCheckBox* m_CPUParallelCB;
		wxButton* m_LoadButton;
		wxButton* m_StoreButton;
		wxStaticText* m_staticText19;
		wxTextCtrl* SAMPLE_TEXT_BOX;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText91;
		wxChoice* AudioInChoiceDropbox;
		wxStaticText* m_staticText181;
		wxSlider* AudioInVolume;
		wxStaticText* lastInSizeText;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText9;
		wxChoice* AudioOutChoiceDropbox;
		wxStaticText* m_staticText18;
		wxSlider* AudioOutVolume;
		wxStaticText* m_staticText911;
		wxChoice* VideoInChoiceDropbox;
		wxToggleButton* videoOnOffButton;
		wxCheckBox* m_FreezeFoveaPosition;
		wxCheckBox* m_freezeScreenAttnSpotCB;
		wxStaticBitmap* AudioInFFTBitmapWidget;
		wxStaticBitmap* AudioOutFFTBitmapWidget;
		wxButton* ShowMapWindowButton;
		wxChoice* ViewMapChoice;
		wxStaticText* refreshDelayMSText;
		wxSlider* mapMonitorRefreshDelay;
		wxStaticText* chosenMapText1;
		wxStaticText* chosenMapText2;
		wxStaticText* chosenMapText3;
		wxStaticBitmap* chosenMapBitmap;
		wxStaticText* SelectedMapDetailLabel;
		wxTimer MonitorFrameTick;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnMonitorWindowActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnMonitorWindowActivateApp( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnMonitorWindowClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnPaintFrameErase( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnMonitorWindowHibernate( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnMonitorWindowIconize( wxIconizeEvent& event ) { event.Skip(); }
		virtual void OnMonitorWindowIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnPaintFrame( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnRunToggleButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStep( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnContinueButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReloadLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetLayoutButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestAClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTestBClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGoodClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBadClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void DoLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void DoStore( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNeuronFactorsChangeUpdateClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRevertNeuronFactorsClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNeuronFactorsDefaultsClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void ON_SAMPLE_TEXT( wxCommandEvent& event ) { event.Skip(); }
		virtual void ON_SAMPLE_ON_ENTER( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioInDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeIn( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnAudioOutDeviceChoiceChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAudioVolumeOut( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnVideoInChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVideoOnOffToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFreezeFoveaCB( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFreezeScreenAttnSpotCB( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewMapMonitorWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMapChoiceChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScrollMapMonitorMsSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnMonitorFrameTickTimer( wxTimerEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* m_SettingsH0;
		wxButton* m_updateCortexFactorsButton;
		wxBoxSizer* m_SettingsH1;
		wxButton* m_UndoButton17;
		wxBoxSizer* m_SettingsH2;
		wxButton* m_DefaultsButton;
		wxStaticText* MonitorStatisticsLine1;
		wxStaticText* MonitorStatisticsLine2;
		wxStaticText* MonitorStatisticsLine3;
		wxRichTextCtrl* LogRichText;
		
		MonitorFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Monitor - Debug"), const wxPoint& pos = wxPoint( -1,-1 ), const wxSize& size = wxSize( 2400,1020 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MonitorFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TopVideoFrameGen
///////////////////////////////////////////////////////////////////////////////
class TopVideoFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxCheckBox* cameraLowResCB;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* TopVideoFrameVertLayout;
		wxCheckBox* cameraFoveaSoptCB;
		
		TopVideoFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22 - Video"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 656,545 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~TopVideoFrameGen();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TopTextFrameGen
///////////////////////////////////////////////////////////////////////////////
class TopTextFrameGen : public wxFrame 
{
	private:
	
	protected:
		wxTextCtrl* TextIn;
		wxButton* TextInClearButton;
		wxTextCtrl* TextOut;
		wxButton* TextOutClearButton1;
		wxTimer textWindowTick;
		
		// Virtual event handlers, overide them in your derived class
		virtual void TextInOnChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTextInChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnTextInClearButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTextOutClearButton( wxCommandEvent& event ) { event.Skip(); }
		virtual void TextWindowTick( wxTimerEvent& event ) { event.Skip(); }
		
	
	public:
		
		TopTextFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS22-Text"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,694 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
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
		wxTimer m_timer3;
		
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
		virtual void OnTimerTick( wxTimerEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* WhiteboardHorizPanel;
		
		WhiteboardFrameGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SRS - Whiteboard"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,500 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~WhiteboardFrameGen();
	
};

#endif //__SRS22UIGEN_H__
