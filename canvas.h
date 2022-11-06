#pragma once
///////////////////////////////////////////////////////////////////////////////
// Name:        samples/image/canvas.h
// Purpose:     sample showing operations with wxImage
// Author:      Robert Roebling
// Modified by: Francesco Montorsi
// Created:     1998
// Copyright:   (c) 1998-2005 Robert Roebling
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "wx/scrolwin.h"

//-----------------------------------------------------------------------------
// MyCanvas
//-----------------------------------------------------------------------------

namespace SRS22 {
	class MyCanvas;

	class MyCanvasPainter {
	public:
		virtual void OnPostPaint(wxPaintDC* DC, wxPaintEvent& event) = 0;
	};

	class MyCanvas : public wxWindow
	{
	public:
		MyCanvas(wxWindow* parent, wxWindowID, const wxPoint& pos, const wxSize& size);
		~MyCanvas();

		void OnEraseBackground(wxEraseEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnMouseLeft(wxMouseEvent& event);
		void OnMouseMove(wxMouseEvent& event);

		void Clear();
		// Does not do a repaint.
		void SetPixel(wxColor c, wxPoint pt, int thickness = 1);

		wxBitmap  backingStore;
		/// <summary>
		/// Also defines the "current color" to draw with.
		/// </summary>
		wxBrush currentBrush;

		/// <summary>
		/// The canvas may have zero or one callback at the end of OnPaint
		/// to allow a owenr to draw something.
		/// </summary>
		MyCanvasPainter* OnPaintPostListener = NULL;

		void SetEraseBackground(bool erase);

	private:
		bool _eraseBackgroundFlag = false;
		wxBitmap m_bmpSmileXpm;
		wxIcon   m_iconSmileXpm;

		wxDECLARE_EVENT_TABLE();
	};
}