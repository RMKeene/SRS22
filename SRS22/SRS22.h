// SRS22.h : main header file for the SRS22 application
//
#pragma once

#include "SRS22UIgen.h"
#include "MonitorFrame.h"
#include "TopTextFrame.h"
#include "WhiteboardFrame.h"
#include "TopVideoFrame.h"

namespace SRS22 {
	// Define a new application type, each program should derive a class from wxApp
	class SRS22App : public wxApp
	{
	public:
		SRS22App();
		~SRS22App();
		// override base class virtuals
		// ----------------------------

		// this one is called on application startup and is a good place for the app
		// initialization (doing it here and not in the ctor allows to have an error
		// return: if OnInit() returns false, the application terminates)
		virtual bool OnInit() wxOVERRIDE;

		MonitorFrame* monitorFrame;

	private:
		wxLocale m_locale;
	};

	wxIMPLEMENT_APP(SRS22App);
}
