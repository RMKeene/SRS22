///////////////////////////////////////////////////////////////////////////////
// Name:        samples/image/canvas.cpp
// Purpose:     sample showing operations with wxImage
// Author:      Robert Roebling
// Modified by: Francesco Montorsi
// Created:     1998
// Copyright:   (c) 1998-2005 Robert Roebling
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/image.h"
#include "wx/file.h"
#include "wx/filename.h"
#include "wx/mstream.h"
#include "wx/wfstream.h"
#include "wx/quantize.h"
#include "wx/stopwatch.h"

#if wxUSE_CLIPBOARD
#include "wx/dataobj.h"
#include "wx/clipbrd.h"
#endif // wxUSE_CLIPBOARD

#include "canvas.h"

namespace SRS22 {

	//-----------------------------------------------------------------------------
	// MyCanvas
	//-----------------------------------------------------------------------------

	wxBEGIN_EVENT_TABLE(MyCanvas, wxWindow)
		EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
		EVT_PAINT(MyCanvas::OnPaint)
		EVT_LEFT_DOWN(MyCanvas::OnMouseLeft)
		EVT_MOTION(MyCanvas::OnMouseMove)
		wxEND_EVENT_TABLE()

		MyCanvas::MyCanvas(wxWindow* parent, wxWindowID id,
			const wxPoint& pos, const wxSize& size)
		: wxWindow(parent, id, pos, size, wxSUNKEN_BORDER),
		backingStore()
	{
		backingStore.Create(size.x, size.y, 24);
		Clear();
	}

	void MyCanvas::Clear() {
		wxMemoryDC dc;
		dc.SelectObject(backingStore);
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.DrawRectangle(0, 0, GetSize().x, GetSize().y);
		dc.SelectObject(wxNullBitmap);
	}

	void MyCanvas::SetPixel(wxColor c, wxPoint pt, int thickness) {
		wxMemoryDC dc;
		dc.SelectObject(backingStore);
		dc.SetBrush(currentBrush);
		dc.SetPen(wxPen(c, thickness, wxPENSTYLE_SOLID));
		if (thickness <= 1)
			dc.DrawPoint(pt);
		else
			dc.DrawCircle(pt, thickness / 2);
		dc.SelectObject(wxNullBitmap);
	}

	MyCanvas::~MyCanvas()
	{
	}

	void MyCanvas::OnEraseBackground(wxEraseEvent& event) {
		// do nothing
	}

	void MyCanvas::OnPaint(wxPaintEvent& event)
	{
		wxPaintDC dc(this);
		PrepareDC(dc);

		dc.DrawBitmap(backingStore, 0, 0);

		//dc.DrawText("Drawn directly", 150, 10);
		//dc.SetBrush(wxBrush("orange"));
		//dc.SetPen(*wxBLACK_PEN);
		//dc.DrawRectangle(150, 30, 100, 100);
		//dc.SetBrush(*wxWHITE_BRUSH);
		//dc.DrawRectangle(170, 50, 60, 60);

		if (OnPaintPostListener)
			OnPaintPostListener->OnPostPaint(&dc, event);
	}

	void MyCanvas::OnMouseLeft(wxMouseEvent& event) {
		if (currentBrush.IsOk()) {
			SetPixel(currentBrush.GetColour(), wxPoint(event.GetX(), event.GetY()), event.m_shiftDown ? 4 : 1);
			Refresh();
		}
	}

	void MyCanvas::OnMouseMove(wxMouseEvent& event) {
		if (event.Dragging()) {
			if (currentBrush.IsOk()) {
				SetPixel(currentBrush.GetColour(), wxPoint(event.GetX(), event.GetY()), event.m_shiftDown ? 4 : 1);
				Refresh();
			}
		}
	}

}