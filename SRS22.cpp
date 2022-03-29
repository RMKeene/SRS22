
// SRS22.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "SRS22.h"
#include "ini.h"
#include "Settings.h"

SRS22App::SRS22App() : 
	// Locale affects on the language used in the calendar, and may affect
	// on the first day of the week.
	m_locale(wxLANGUAGE_DEFAULT)
{
	Settings::globalSettings.Load();
}

SRS22App::~SRS22App() {
}

// `Main program' equivalent: the program execution "starts" here
bool SRS22App::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	

	monitorFrame = new MonitorFrame(nullptr);
	monitorFrame->Show(true);

	// success: wxApp::OnRun() will be called which will enter the main message
	// loop and the application will run. If we returned false here, the
	// application would exit immediately.
	return true;
}
