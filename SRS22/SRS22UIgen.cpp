///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SRS22UIgen.h"

#include "ui/ColorSquare16Black.bmp.h"
#include "ui/ColorSquare16Blue.bmp.h"
#include "ui/ColorSquare16Cyan.bmp.h"
#include "ui/ColorSquare16Green.bmp.h"
#include "ui/ColorSquare16Magenta.bmp.h"
#include "ui/ColorSquare16Red.bmp.h"
#include "ui/ColorSquare16White.bmp.h"
#include "ui/ColorSquare16Yellow.bmp.h"

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
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Tick") ), wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	RunButton = new wxToggleButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Run"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( RunButton, 0, wxALL, 5 );
	
	MonitorStepButton = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Step"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( MonitorStepButton, 0, wxALL, 5 );
	
	ContinueButton = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Continue"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( ContinueButton, 0, wxALL, 5 );
	
	
	sbSizer10->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	TickCountText = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Ticks: 0000000000"), wxDefaultPosition, wxDefaultSize, 0 );
	TickCountText->Wrap( -1 );
	bSizer15->Add( TickCountText, 0, wxALL, 5 );
	
	TicksPerSecondText = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Ticks/Sec.: 000.000"), wxDefaultPosition, wxDefaultSize, 0 );
	TicksPerSecondText->Wrap( -1 );
	TicksPerSecondText->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer15->Add( TicksPerSecondText, 0, wxALL, 5 );
	
	
	sbSizer10->Add( bSizer15, 1, wxEXPAND, 5 );
	
	
	MonitorControl->Add( sbSizer10, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Window Layout") ), wxHORIZONTAL );
	
	saveLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( saveLayoutButton, 0, wxALL, 5 );
	
	reloadLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Reload"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( reloadLayoutButton, 0, wxALL, 5 );
	
	resetLayoutButton = new wxButton( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer8->Add( resetLayoutButton, 0, wxALL, 5 );
	
	
	MonitorControl->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Test") ), wxHORIZONTAL );
	
	TerstAButton = new wxButton( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Test A"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( TerstAButton, 0, wxALL, 5 );
	
	TestBButton = new wxButton( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Test B"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer11->Add( TestBButton, 0, wxALL, 5 );
	
	
	MonitorControl->Add( sbSizer11, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer111;
	sbSizer111 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Reward/Punish") ), wxVERTICAL );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );
	
	GoodButton = new wxButton( sbSizer111->GetStaticBox(), wxID_ANY, wxT("Good!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( GoodButton, 0, wxALL, 5 );
	
	BadButton = new wxButton( sbSizer111->GetStaticBox(), wxID_ANY, wxT("Bad!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer16->Add( BadButton, 0, wxALL, 5 );
	
	
	sbSizer111->Add( bSizer16, 1, wxEXPAND, 5 );
	
	overallGoodnessLabel = new wxStaticText( sbSizer111->GetStaticBox(), wxID_ANY, wxT("Goodness: 0.0"), wxDefaultPosition, wxDefaultSize, 0 );
	overallGoodnessLabel->Wrap( -1 );
	sbSizer111->Add( overallGoodnessLabel, 0, wxALL, 5 );
	
	
	MonitorControl->Add( sbSizer111, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer141;
	sbSizer141 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("CPU") ), wxVERTICAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	m_CPUParallelCB = new wxCheckBox( sbSizer141->GetStaticBox(), wxID_ANY, wxT("Parallel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_CPUParallelCB->SetValue(true); 
	bSizer17->Add( m_CPUParallelCB, 0, wxALL, 5 );
	
	
	sbSizer141->Add( bSizer17, 1, wxEXPAND, 5 );
	
	
	MonitorControl->Add( sbSizer141, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("File") ), wxVERTICAL );
	
	m_LoadButton = new wxButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_LoadButton, 0, wxALL, 5 );
	
	m_StoreButton = new wxButton( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Store"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( m_StoreButton, 0, wxALL, 5 );
	
	
	MonitorControl->Add( sbSizer16, 0, wxEXPAND, 5 );
	
	
	MonitorControl->Add( 0, 0, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer161;
	sbSizer161 = new wxStaticBoxSizer( new wxStaticBox( MonitorControl->GetStaticBox(), wxID_ANY, wxT("Neuron/Cortex Factors") ), wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_updateCotrexFactorsButton = new wxButton( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Update"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	bSizer18->Add( m_updateCotrexFactorsButton, 0, wxALL, 5 );
	
	m_button17 = new wxButton( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Undo"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer18->Add( m_button17, 0, wxALL, 5 );
	
	m_button18 = new wxButton( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Defaults"), wxDefaultPosition, wxSize( 60,-1 ), 0 );
	bSizer18->Add( m_button18, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("En+ / tick"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer18->Add( m_staticText19, 0, wxALL, 5 );
	
	m_EnergyTextInput = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.02"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_EnergyTextInput->SetMaxLength( 6 ); 
	bSizer18->Add( m_EnergyTextInput, 0, wxALL, 5 );
	
	m_staticText22 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("En Th: Low"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer18->Add( m_staticText22, 0, wxALL, 5 );
	
	m_LowEnergyThreshTextInput = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.1"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer18->Add( m_LowEnergyThreshTextInput, 0, wxALL, 5 );
	
	m_hiLabel = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Hi"), wxDefaultPosition, wxDefaultSize, 0 );
	m_hiLabel->Wrap( -1 );
	bSizer18->Add( m_hiLabel, 0, wxALL, 5 );
	
	m_hiEnergyThresh = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.9"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer18->Add( m_hiEnergyThresh, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Fire Dep."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer18->Add( m_staticText24, 0, wxALL, 5 );
	
	m_fireDepletion = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.05"), wxDefaultPosition, wxSize( 70,-1 ), 0 );
	bSizer18->Add( m_fireDepletion, 0, wxALL, 5 );
	
	m_staticline2 = new wxStaticLine( sbSizer161->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer18->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText31 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Conf: Rate  +"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer18->Add( m_staticText31, 0, wxALL, 5 );
	
	m_confidenceUpRate = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("1.01"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer18->Add( m_confidenceUpRate, 0, wxALL, 5 );
	
	m_confidenceDownRateLabel = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	m_confidenceDownRateLabel->Wrap( -1 );
	bSizer18->Add( m_confidenceDownRateLabel, 0, wxALL, 5 );
	
	m_confidenceDownRate = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.999"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer18->Add( m_confidenceDownRate, 0, wxALL, 5 );
	
	m_staticText33 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Clip: Min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer18->Add( m_staticText33, 0, wxALL, 5 );
	
	m_minConfidence = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.0001"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer18->Add( m_minConfidence, 0, wxALL, 5 );
	
	m_staticText34 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	bSizer18->Add( m_staticText34, 0, wxALL, 5 );
	
	m_maxConfidence = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.999"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer18->Add( m_maxConfidence, 0, wxALL, 5 );
	
	
	sbSizer161->Add( bSizer18, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText25 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Conn Throttle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer19->Add( m_staticText25, 0, wxALL, 5 );
	
	m_ConnectionThrottle = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("1.0"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_ConnectionThrottle->SetMaxLength( 6 ); 
	bSizer19->Add( m_ConnectionThrottle, 0, wxALL, 5 );
	
	m_staticText26 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Link Match Sharpness"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText26->Wrap( -1 );
	bSizer19->Add( m_staticText26, 0, wxALL, 5 );
	
	m_linkMatchSharpness = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("10"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_linkMatchSharpness, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Gwth"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer19->Add( m_staticText21, 0, wxALL, 5 );
	
	m_GrowthRateTextInput = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.01"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_GrowthRateTextInput->SetMaxLength( 8 ); 
	bSizer19->Add( m_GrowthRateTextInput, 0, wxALL, 5 );
	
	m_staticline4 = new wxStaticLine( sbSizer161->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer19->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText27 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Reroute: Th"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	bSizer19->Add( m_staticText27, 0, wxALL, 5 );
	
	m_RerouteThreshold = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.001"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer19->Add( m_RerouteThreshold, 0, wxALL, 5 );
	
	m_staticText35 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Prob"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	bSizer19->Add( m_staticText35, 0, wxALL, 5 );
	
	m_rerouteProbabilityTextInput = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.01"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_rerouteProbabilityTextInput, 0, wxALL, 5 );
	
	m_staticText36 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Init Conf"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer19->Add( m_staticText36, 0, wxALL, 5 );
	
	m_rerouteInitialConfidence = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.5"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_rerouteInitialConfidence, 0, wxALL, 5 );
	
	m_staticline3 = new wxStaticLine( sbSizer161->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer19->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText28 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Low Learn Th"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	m_staticText28->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );
	
	bSizer19->Add( m_staticText28, 0, wxALL, 5 );
	
	m_lowLearnThresh = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.25"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_lowLearnThresh, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Learn: Low"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer19->Add( m_staticText29, 0, wxALL, 5 );
	
	m_lowLearnRate = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.01"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_lowLearnRate, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( sbSizer161->GetStaticBox(), wxID_ANY, wxT("Hi"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer19->Add( m_staticText30, 0, wxALL, 5 );
	
	m_hiLearnRate = new wxTextCtrl( sbSizer161->GetStaticBox(), wxID_ANY, wxT("0.05"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	bSizer19->Add( m_hiLearnRate, 0, wxALL, 5 );
	
	
	sbSizer161->Add( bSizer19, 1, wxEXPAND, 5 );
	
	
	MonitorControl->Add( sbSizer161, 0, wxEXPAND, 5 );
	
	
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
	
	lastInSizeText = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Last In Size 0"), wxDefaultPosition, wxDefaultSize, 0 );
	lastInSizeText->Wrap( -1 );
	lastInSizeText->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer26->Add( lastInSizeText, 0, wxALL, 5 );
	
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
	
	videoOnOffButton = new wxToggleButton( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Video On/Off"), wxDefaultPosition, wxDefaultSize, 0 );
	videoOnOffButton->SetValue( true ); 
	bSizer31->Add( videoOnOffButton, 0, wxALL, 5 );
	
	m_FreezeFoveaPosition = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Freeze Fovea Pos."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_FreezeFoveaPosition, 0, wxALL, 5 );
	
	m_freezeScreenAttnSpotCB = new wxCheckBox( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Freeze Screen Attn. Spot"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer31->Add( m_freezeScreenAttnSpotCB, 0, wxALL, 5 );
	
	
	bSizer30->Add( bSizer31, 0, wxEXPAND, 5 );
	
	
	bSizer30->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer27->Add( bSizer30, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( sbSizer13->GetStaticBox(), wxID_ANY, wxT("In FFT, Out FFT") ), wxHORIZONTAL );
	
	AudioInFFTBitmapWidget = new wxStaticBitmap( sbSizer14->GetStaticBox(), wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 128,128 ), 0 );
	sbSizer14->Add( AudioInFFTBitmapWidget, 0, wxALL, 5 );
	
	AudioOutFFTBitmapWidget = new wxStaticBitmap( sbSizer14->GetStaticBox(), wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 128,128 ), 0 );
	sbSizer14->Add( AudioOutFFTBitmapWidget, 0, wxALL, 5 );
	
	
	bSizer27->Add( sbSizer14, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Map Monitor") ), wxHORIZONTAL );
	
	sbSizer12->SetMinSize( wxSize( 1400,500 ) ); 
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer13->Add( 0, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	ShowMapWindowButton = new wxButton( sbSizer12->GetStaticBox(), wxID_ANY, wxT("New Window"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( ShowMapWindowButton, 0, wxALL, 5 );
	
	wxString ViewMapChoiceChoices[] = { wxT("None") };
	int ViewMapChoiceNChoices = sizeof( ViewMapChoiceChoices ) / sizeof( wxString );
	ViewMapChoice = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, ViewMapChoiceNChoices, ViewMapChoiceChoices, 0 );
	ViewMapChoice->SetSelection( 0 );
	bSizer10->Add( ViewMapChoice, 0, wxALL, 5 );
	
	refreshDelayMSText = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Refresh 200 ms."), wxDefaultPosition, wxDefaultSize, 0 );
	refreshDelayMSText->Wrap( -1 );
	bSizer10->Add( refreshDelayMSText, 0, wxALL, 5 );
	
	mapMonitorRefreshDelay = new wxSlider( sbSizer12->GetStaticBox(), wxID_ANY, 200, 1, 1000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer10->Add( mapMonitorRefreshDelay, 0, wxALL, 5 );
	
	
	bSizer14->Add( bSizer10, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	chosenMapText1 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("No Map Selected"), wxDefaultPosition, wxDefaultSize, 0 );
	chosenMapText1->Wrap( -1 );
	bSizer11->Add( chosenMapText1, 0, wxALL, 1 );
	
	chosenMapText2 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	chosenMapText2->Wrap( -1 );
	bSizer11->Add( chosenMapText2, 0, wxALL, 1 );
	
	chosenMapText3 = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	chosenMapText3->Wrap( -1 );
	bSizer11->Add( chosenMapText3, 0, wxALL, 5 );
	
	chosenMapBitmap = new wxStaticBitmap( sbSizer12->GetStaticBox(), wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 200,200 ), 0 );
	bSizer11->Add( chosenMapBitmap, 0, wxALL, 2 );
	
	
	bSizer14->Add( bSizer11, 0, wxEXPAND, 1 );
	
	
	bSizer13->Add( bSizer14, 0, wxEXPAND, 5 );
	
	SelectedMapDetailLabel = new wxStaticText( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Map Detail:"), wxDefaultPosition, wxDefaultSize, 0 );
	SelectedMapDetailLabel->Wrap( -1 );
	bSizer13->Add( SelectedMapDetailLabel, 0, wxALL, 5 );
	
	
	sbSizer12->Add( bSizer13, 0, wxEXPAND, 5 );
	
	
	bSizer27->Add( sbSizer12, 0, wxEXPAND, 5 );
	
	
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
	LogRichText->SetBackgroundColour( wxColour( 103, 103, 103 ) );
	
	MonitorLogSubframe->Add( LogRichText, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer3->Add( MonitorLogSubframe, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	MonitorFrameTick.SetOwner( this, wxID_ANY );
	MonitorFrameTick.Start( 100 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowActivate ) );
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowActivateApp ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MonitorFrameGen::OnMonitorWindowClose ) );
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MonitorFrameGen::OnPaintFrameErase ) );
	this->Connect( wxEVT_HIBERNATE, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowHibernate ) );
	this->Connect( wxEVT_ICONIZE, wxIconizeEventHandler( MonitorFrameGen::OnMonitorWindowIconize ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( MonitorFrameGen::OnMonitorWindowIdle ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( MonitorFrameGen::OnPaintFrame ) );
	RunButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRunToggleButton ), NULL, this );
	MonitorStepButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnStep ), NULL, this );
	ContinueButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnContinueButton ), NULL, this );
	saveLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnSaveLayoutButton ), NULL, this );
	reloadLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnReloadLayoutButton ), NULL, this );
	resetLayoutButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnResetLayoutButton ), NULL, this );
	TerstAButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnTestAClicked ), NULL, this );
	TestBButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnTestBClicked ), NULL, this );
	GoodButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnGoodClicked ), NULL, this );
	BadButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnBadClicked ), NULL, this );
	m_LoadButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::DoLoad ), NULL, this );
	m_StoreButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::DoStore ), NULL, this );
	m_updateCotrexFactorsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNeuronFactorsChangeUpdateClicked ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRevertNeuronFactorsClicked ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNeuronFactorsDefaultsClicked ), NULL, this );
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
	videoOnOffButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnVideoOnOffToggle ), NULL, this );
	m_FreezeFoveaPosition->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnFreezeFoveaCB ), NULL, this );
	m_freezeScreenAttnSpotCB->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnFreezeScreenAttnSpotCB ), NULL, this );
	ShowMapWindowButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNewMapMonitorWindow ), NULL, this );
	ViewMapChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnMapChoiceChange ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MonitorFrameGen::OnMonitorFrameTickTimer ) );
}

MonitorFrameGen::~MonitorFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowActivate ) );
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowActivateApp ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MonitorFrameGen::OnMonitorWindowClose ) );
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MonitorFrameGen::OnPaintFrameErase ) );
	this->Disconnect( wxEVT_HIBERNATE, wxActivateEventHandler( MonitorFrameGen::OnMonitorWindowHibernate ) );
	this->Disconnect( wxEVT_ICONIZE, wxIconizeEventHandler( MonitorFrameGen::OnMonitorWindowIconize ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MonitorFrameGen::OnMonitorWindowIdle ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MonitorFrameGen::OnPaintFrame ) );
	RunButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRunToggleButton ), NULL, this );
	MonitorStepButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnStep ), NULL, this );
	ContinueButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnContinueButton ), NULL, this );
	saveLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnSaveLayoutButton ), NULL, this );
	reloadLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnReloadLayoutButton ), NULL, this );
	resetLayoutButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnResetLayoutButton ), NULL, this );
	TerstAButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnTestAClicked ), NULL, this );
	TestBButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnTestBClicked ), NULL, this );
	GoodButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnGoodClicked ), NULL, this );
	BadButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnBadClicked ), NULL, this );
	m_LoadButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::DoLoad ), NULL, this );
	m_StoreButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::DoStore ), NULL, this );
	m_updateCotrexFactorsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNeuronFactorsChangeUpdateClicked ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnRevertNeuronFactorsClicked ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNeuronFactorsDefaultsClicked ), NULL, this );
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
	videoOnOffButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnVideoOnOffToggle ), NULL, this );
	m_FreezeFoveaPosition->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnFreezeFoveaCB ), NULL, this );
	m_freezeScreenAttnSpotCB->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnFreezeScreenAttnSpotCB ), NULL, this );
	ShowMapWindowButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MonitorFrameGen::OnNewMapMonitorWindow ), NULL, this );
	ViewMapChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MonitorFrameGen::OnMapChoiceChange ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	mapMonitorRefreshDelay->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MonitorFrameGen::OnScrollMapMonitorMsSlider ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MonitorFrameGen::OnMonitorFrameTickTimer ) );
	
}

TopVideoFrameGen::TopVideoFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 200,200 ), wxDefaultSize );
	
	TopVideoFrameVertLayout = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer12->SetMinSize( wxSize( -1,24 ) ); 
	cameraFoveaSoptCB = new wxCheckBox( this, wxID_ANY, wxT("Fovea Spot"), wxDefaultPosition, wxDefaultSize, 0 );
	cameraFoveaSoptCB->SetValue(true); 
	bSizer12->Add( cameraFoveaSoptCB, 0, wxALL, 5 );
	
	cameraLowResCB = new wxCheckBox( this, wxID_ANY, wxT("LowRes"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( cameraLowResCB, 0, wxALL, 5 );
	
	
	TopVideoFrameVertLayout->Add( bSizer12, 0, wxEXPAND, 1 );
	
	
	this->SetSizer( TopVideoFrameVertLayout );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE, wxActivateEventHandler( TopVideoFrameGen::OnActivate ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopVideoFrameGen::OnClose ) );
}

TopVideoFrameGen::~TopVideoFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE, wxActivateEventHandler( TopVideoFrameGen::OnActivate ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopVideoFrameGen::OnClose ) );
	
}

TopTextFrameGen::TopTextFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("In") ), wxHORIZONTAL );
	
	TextIn = new wxTextCtrl( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,300 ), wxTE_MULTILINE );
	sbSizer9->Add( TextIn, 0, wxALL, 5 );
	
	TextInClearButton = new wxButton( sbSizer9->GetStaticBox(), wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer9->Add( TextInClearButton, 0, wxALL, 2 );
	
	
	bSizer13->Add( sbSizer9, 1, wxEXPAND, 2 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Out") ), wxHORIZONTAL );
	
	TextOut = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,300 ), wxTE_MULTILINE );
	sbSizer10->Add( TextOut, 0, wxALL, 5 );
	
	TextOutClearButton1 = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer10->Add( TextOutClearButton1, 0, wxALL, 2 );
	
	
	bSizer13->Add( sbSizer10, 1, wxEXPAND, 2 );
	
	
	this->SetSizer( bSizer13 );
	this->Layout();
	textWindowTick.SetOwner( this, wxID_ANY );
	textWindowTick.Start( 100 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CHAR, wxKeyEventHandler( TopTextFrameGen::TextInOnChar ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopTextFrameGen::OnClose ) );
	TextIn->Connect( wxEVT_CHAR, wxKeyEventHandler( TopTextFrameGen::OnTextInChar ), NULL, this );
	TextInClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextInClearButton ), NULL, this );
	TextOutClearButton1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextOutClearButton ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( TopTextFrameGen::TextWindowTick ) );
}

TopTextFrameGen::~TopTextFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CHAR, wxKeyEventHandler( TopTextFrameGen::TextInOnChar ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TopTextFrameGen::OnClose ) );
	TextIn->Disconnect( wxEVT_CHAR, wxKeyEventHandler( TopTextFrameGen::OnTextInChar ), NULL, this );
	TextInClearButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextInClearButton ), NULL, this );
	TextOutClearButton1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopTextFrameGen::OnTextOutClearButton ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( TopTextFrameGen::TextWindowTick ) );
	
}

WhiteboardFrameGen::WhiteboardFrameGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	
	WhiteboardHorizPanel = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Pens") ), wxVERTICAL );
	
	WhiteButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16White_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( WhiteButton, 0, wxALL, 5 );
	
	BlackButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Black_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( BlackButton, 0, wxALL, 5 );
	
	RedButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Red_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( RedButton, 0, wxALL, 5 );
	
	GreenButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Green_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( GreenButton, 0, wxALL, 5 );
	
	BlueButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Blue_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( BlueButton, 0, wxALL, 5 );
	
	YellowButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Yellow_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( YellowButton, 0, wxALL, 5 );
	
	CyanButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Cyan_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( CyanButton, 0, wxALL, 5 );
	
	MagentaButton = new wxBitmapButton( sbSizer9->GetStaticBox(), wxID_ANY, ColorSquare16Magenta_bmp_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	sbSizer9->Add( MagentaButton, 0, wxALL, 5 );
	
	ClearButton = new wxButton( sbSizer9->GetStaticBox(), wxID_ANY, wxT("C"), wxDefaultPosition, wxSize( 25,25 ), 0 );
	ClearButton->SetFont( wxFont( 8, 70, 90, 92, false, wxT("Arial") ) );
	ClearButton->SetMinSize( wxSize( 25,25 ) );
	ClearButton->SetMaxSize( wxSize( 25,25 ) );
	
	sbSizer9->Add( ClearButton, 0, wxALL, 5 );
	
	
	WhiteboardHorizPanel->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( WhiteboardHorizPanel );
	this->Layout();
	m_timer3.SetOwner( this, wxID_ANY );
	m_timer3.Start( 50 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WhiteboardFrameGen::OnClose ) );
	WhiteButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnWhiteButton ), NULL, this );
	BlackButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnBlackButton ), NULL, this );
	RedButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnRedButton ), NULL, this );
	GreenButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnGreenButton ), NULL, this );
	BlueButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnBlueButton ), NULL, this );
	YellowButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnYellowButton ), NULL, this );
	CyanButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnCyanButton ), NULL, this );
	MagentaButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnMagentaButton ), NULL, this );
	ClearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnWhiteboardClearButton ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( WhiteboardFrameGen::OnTimerTick ) );
}

WhiteboardFrameGen::~WhiteboardFrameGen()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WhiteboardFrameGen::OnClose ) );
	WhiteButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnWhiteButton ), NULL, this );
	BlackButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnBlackButton ), NULL, this );
	RedButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnRedButton ), NULL, this );
	GreenButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnGreenButton ), NULL, this );
	BlueButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnBlueButton ), NULL, this );
	YellowButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnYellowButton ), NULL, this );
	CyanButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnCyanButton ), NULL, this );
	MagentaButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnMagentaButton ), NULL, this );
	ClearButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WhiteboardFrameGen::OnWhiteboardClearButton ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( WhiteboardFrameGen::OnTimerTick ) );
	
}
