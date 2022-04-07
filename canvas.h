///////////////////////////////////////////////////////////////////////////////
// Name:        samples/image/canvas.h
// Purpose:     sample showing operations with wxImage
// Author:      Robert Roebling
// Modified by: Francesco Montorsi
// Created:     1998
// Copyright:   (c) 1998-2005 Robert Roebling
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include "wx/scrolwin.h"

//-----------------------------------------------------------------------------
// MyCanvas
//-----------------------------------------------------------------------------

class MyCanvas: public wxWindow
{
public:
    MyCanvas( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size );
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

private:
    wxBitmap m_bmpSmileXpm;
    wxIcon   m_iconSmileXpm;

    wxDECLARE_EVENT_TABLE();
};
