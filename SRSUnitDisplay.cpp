#include "pch.h"
#include "SRSUnitDisplay.h"
#include "StringConversionHelpers.h"

using namespace Gdiplus;

namespace SRS22 {
	void SRSUnitDisplay::DrawInDC(Graphics& g, Gdiplus::Rect& rect, std::shared_ptr<SRSUnit> u, bool showLabel, bool preClearToBlack) {
		cv::Mat& mt = u->M.charges;

		Bitmap bm(mt.cols, mt.rows, PixelFormat24bppRGB);

		if (mt.dims >= 3) {
			for (int c = 0; c < mt.cols; c++) {
				for (int r = 0; r < mt.rows; r++) {
					bm.SetPixel(r, c, Color((BYTE)(mt.at<float>(0, r, c) * 255.0f),
						(BYTE)(mt.at<float>(1, r, c) * 255.0f),
						(BYTE)(mt.at<float>(2, r, c) * 255.0f)));
				}
			}
		}
		else  if (mt.dims == 2) {
			for (int c = 0; c < mt.cols; c++) {
				for (int r = 0; r < mt.rows; r++) {
					const BYTE f = (BYTE)(mt.at<float>(0, r, c) * 255.0f);
					bm.SetPixel(r, c, Color(f, f, f));
				}
			}
		}

		if (preClearToBlack) {
			SolidBrush br(Color::Black);
			Status st = g.FillRectangle(&br, rect);
			assert(st == Ok);
		}

		if (showLabel) {
			SolidBrush br(Color::LightBlue);
			FontFamily ff(L"Arial");
			Font font(&ff, 12);
			std::wstring  wst = StringConversionHelpers::str_2_wstr(u->MapName);
			Status st = g.DrawString(wst.c_str(), -1, &font, PointF(0, 0), &br);
			assert(st == Ok);
		}

		g.DrawImage(&bm, rect);
	}
}