#ifndef COLORSQUARE16BLUE_BMP_H
#define COLORSQUARE16BLUE_BMP_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char ColorSquare16Blue_bmp[] = 
{
	0x42, 0x4D, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3A, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 
	0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC2, 0x0E, 
	0x00, 0x00, 0xC2, 0x0E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0xFF, 0x26, 0x00, 0xFF, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

wxBitmap& ColorSquare16Blue_bmp_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( ColorSquare16Blue_bmp, sizeof( ColorSquare16Blue_bmp ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_BMP );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //COLORSQUARE16BLUE_BMP_H