///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SRS22UIgen.h"

///////////////////////////////////////////////////////////////////////////

MonitorFrameGen::MonitorFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,500 ), wxDefaultSize );
	
	MonitorFrameMenuBar = new wxMenuBar( 0 );
	m_menu5 = new wxMenu();
	wxMenuItem* MonitorMenuNewItem;
	MonitorMenuNewItem = new wxMenuItem( m_menu5, wxID_ANY, wxString( wxT("New") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu5->Append( MonitorMenuNewItem );
	
	wxMenuItem* MonitorOpenMenuItem;
	MonitorOpenMenuItem = new wxMenuItem( m_menu5, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu5->Append( MonitorOpenMenuItem );
	
	wxMenuItem* MonitorMenuSaveItem;
	MonitorMenuSaveItem = new wxMenuItem( m_menu5, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu5->Append( MonitorMenuSaveItem );
	
	wxMenuItem* MonitorMenuSaveAsItem;
	MonitorMenuSaveAsItem = new wxMenuItem( m_menu5, wxID_ANY, wxString( wxT("Save As...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu5->Append( MonitorMenuSaveAsItem );
	
	MonitorFrameMenuBar->Append( m_menu5, wxT("File") ); 
	
	this->SetMenuBar( MonitorFrameMenuBar );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* MonitorControl;
	MonitorControl = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Control") ), wxHORIZONTAL );
	
	MonitorControl->SetMinSize( wxSize( -1,100 ) ); 
	RunButton = new wxToggleButton( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorControl->Add( RunButton, 0, wxALL, 5 );
	
	MonitorStepButton = new wxButton( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Step"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorControl->Add( MonitorStepButton, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Window Layout") ), wxHORIZONTAL );
	
	saveLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( saveLayoutButton, 0, wxALL, 5 );
	
	reloadLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Reload"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( reloadLayoutButton, 0, wxALL, 5 );
	
	resetLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( resetLayoutButton, 0, wxALL, 5 );
	
	
	MonitorControl->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	
	bSizer3->Add( MonitorControl, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("IO Devices") ), wxVERTICAL );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText91 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Audio: In"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	bSizer26->Add( m_staticText91, 0, wxALL, 5 );
	
	wxArrayString AudioInChoiceDropboxChoices;
	AudioInChoiceDropbox = new wxChoice( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, AudioInChoiceDropboxChoices, 0 );
	AudioInChoiceDropbox->SetSelection( 0 );
	bSizer26->Add( AudioInChoiceDropbox, 0, wxALL, 5 );
	
	m_staticText181 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText181->Wrap( -1 );
	bSizer26->Add( m_staticText181, 0, wxALL, 5 );
	
	AudioInVolume = new wxSlider( sbSizer13->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer26->Add( AudioInVolume, 0, wxALL, 5 );
	
	m_staticline1 = new wxStaticLine( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer26->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText9 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Out"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer26->Add( m_staticText9, 0, wxALL, 5 );
	
	wxArrayString AudioOutChoiceDropboxChoices;
	AudioOutChoiceDropbox = new wxChoice( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, AudioOutChoiceDropboxChoices, 0 );
	AudioOutChoiceDropbox->SetSelection( 0 );
	bSizer26->Add( AudioOutChoiceDropbox, 0, wxALL, 5 );
	
	m_staticText18 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Volume"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer26->Add( m_staticText18, 0, wxALL, 5 );
	
	AudioOutVolume = new wxSlider( sbSizer13->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer26->Add( AudioOutVolume, 0, wxALL, 5 );
	
	
	bSizer30->Add( bSizer26, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText911 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Video: In"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText911->Wrap( -1 );
	bSizer31->Add( m_staticText911, 0, wxALL, 5 );
	
	wxArrayString VideoInChoiceDropboxChoices;
	VideoInChoiceDropbox = new wxChoice( sbSizer13->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, VideoInChoiceDropboxChoices, 0 );
	VideoInChoiceDropbox->SetSelection( 0 );
	bSizer31->Add( VideoInChoiceDropbox, 0, wxALL, 5 );
	
	
	bSizer30->Add( bSizer31, 0, wxEXPAND, 5 );
	
	
	bSizer30->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer27->Add( bSizer30, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( sbSizer13->GetStaticBox(), wxID_ANY, wxT("In FFT, Out FFT") ), wxHORIZONTAL );
	
	AudioInFFTBitmapWidget = new wxStaticBitmap( sbSizer14->GetStaticBox(), wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 128,128 ), 0 );
	sbSizer14->Add( AudioInFFTBitmapWidget, 0, wxALL, 5 );
	
	AudioOutFFTBitmapWidget = new wxStaticBitmap( sbSizer14->GetStaticBox(), wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 128,128 ), 0 );
	sbSizer14->Add( AudioOutFFTBitmapWidget, 0, wxALL, 5 );
	
	
	bSizer27->Add( sbSizer14, 1, wxEXPAND, 5 );
	
	
	bSizer27->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	sbSizer13->Add( bSizer27, 1, wxEXPAND, 5 );
	
	
	bSizer3->Add( sbSizer13, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* MonitorStatistics;
	MonitorStatistics = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Statistics") ), wxVERTICAL );
	
	MonitorStatisticsLine1 = new wxStaticText( MonitorStatistics->GetStaticBox(), wxID_ANY, wxT("Step: 0000000"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorStatisticsLine1->Wrap( -1 );
	MonitorStatistics->Add( MonitorStatisticsLine1, 0, wxALL, 5 );
	
	MonitorStatisticsLine2 = new wxStaticText( MonitorStatistics->GetStaticBox(), wxID_ANY, wxT("Step: 0000000"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorStatisticsLine2->Wrap( -1 );
	MonitorStatistics->Add( MonitorStatisticsLine2, 0, wxALL, 5 );
	
	MonitorStatisticsLine3 = new wxStaticText( MonitorStatistics->GetStaticBox(), wxID_ANY, wxT("Step: 0000000"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorStatisticsLine3->Wrap( -1 );
	MonitorStatistics->Add( MonitorStatisticsLine3, 0, wxALL, 5 );
	
	MonitorStatisticsLine4 = new wxStaticText( MonitorStatistics->GetStaticBox(), wxID_ANY, wxT("Step: 0000000"), wxDefaultPosition, wxDefaultSize, 0 );
	MonitorStatisticsLine4->Wrap( -1 );
	MonitorStatistics->Add( MonitorStatisticsLine4, 0, wxALL, 5 );
	
	
	bSizer3->Add( MonitorStatistics, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* MonitorLogSubframe;
	MonitorLogSubframe = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Log") ), wxVERTICAL );
	
	MonitorLogSubframe->SetMinSize( wxSize( -1,400 ) ); 
	LogRichText = new wxRichTextCtrl( MonitorLogSubframe->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	MonitorLogSubframe->Add( LogRichText, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer3->Add( MonitorLogSubframe, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	RunButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRunToggleButton ), NULL, this );
	MonitorStepButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnStep ), NULL, this );
	saveLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnSaveLayoutButton ), NULL, this );
	reloadLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnReloadLayoutButton ), NULL, this );
	resetLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnResetLayoutButton ), NULL, this );
	AudioInChoiceDropbox->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnAudioInDeviceChoiceChanged ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioOutChoiceDropbox->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnAudioOutDeviceChoiceChanged ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	VideoInChoiceDropbox->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnVideoInChanged ), NULL, this );
}

MonitorFrameGen::~MonitorFrameGen()
{
	// Disconnect Events
	RunButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRunToggleButton ), NULL, this );
	MonitorStepButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnStep ), NULL, this );
	saveLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnSaveLayoutButton ), NULL, this );
	reloadLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnReloadLayoutButton ), NULL, this );
	resetLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnResetLayoutButton ), NULL, this );
	AudioInChoiceDropbox->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnAudioInDeviceChoiceChanged ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioInVolume->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeIn ), NULL, this );
	AudioOutChoiceDropbox->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnAudioOutDeviceChoiceChanged ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	AudioOutVolume->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnAudioVolumeOut ), NULL, this );
	VideoInChoiceDropbox->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnVideoInChanged ), NULL, this );
	
}

TopVideoFrameGen::TopVideoFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 200,200 ), wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	TopVideoPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 256,256 ), wxTAB_TRAVERSAL );
	bSizer13->Add( TopVideoPanel, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopVideoFrameGen::OnClose ) );
}

TopVideoFrameGen::~TopVideoFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopVideoFrameGen::OnClose ) );
	
}

TopTextFrameGen::TopTextFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("In") ), wxHORIZONTAL );
	
	TextInClearButton = new wxButton( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( TextInClearButton, 0, wxALL, 2 );
	
	TextInRichText = new wxRichTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	sbSizer9->Add( TextInRichText, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer13->Add( sbSizer9, 1, wxEXPAND, 2 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Out") ), wxHORIZONTAL );
	
	TextOutClearButton1 = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( TextOutClearButton1, 0, wxALL, 2 );
	
	TextOutRichText = new wxRichTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	sbSizer10->Add( TextOutRichText, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer13->Add( sbSizer10, 1, wxEXPAND, 2 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopTextFrameGen::OnClose ) );
	TextInClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextInClearButton ), NULL, this );
	TextOutClearButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextOutClearButton ), NULL, this );
}

TopTextFrameGen::~TopTextFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopTextFrameGen::OnClose ) );
	TextInClearButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextInClearButton ), NULL, this );
	TextOutClearButton1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextOutClearButton ), NULL, this );
	
}

WhiteboardFrameGen::WhiteboardFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	whiteboardCanvas = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	whiteboardCanvas->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer8->Add( whiteboardCanvas, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WhiteboardFrameGen::OnClose ) );
}

WhiteboardFrameGen::~WhiteboardFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WhiteboardFrameGen::OnClose ) );
	
}
