#pragma once
#include "Point.h"
namespace SRS22 {

	/// <summary>
	/// Immutable Rect. Asserts non-negative width and height.
	/// </summary>
	class Rect {
		int halfWidth;
		int halfHeight;
	public:
		int X;
		int Y;
		int width;
		int height;

		const int left() const { return X; }
		/// <summary>
		/// One pixel off the left edge.
		/// return X + width;
		/// </summary>
		/// <returns></returns>
		const int right() const { return X + width; }
		const int top() const { return Y; }
		/// <summary>
		/// One pixel off the bottom edge.
		/// return Y + height;
		/// </summary>
		/// <returns></returns>		
		const int bottom() const { return Y + height; }
		const int halfW() const { return halfWidth; }
		const int halfH() const { return halfHeight; }
		Point Center() { return Point(X + halfWidth, Y + halfHeight); }
		const int CenterX() { return X + halfWidth; }
		const int CenterY() { return Y + halfHeight; }

		Rect() : X(0), Y(0), width(0), height(0), halfWidth(0 / 2), halfHeight(0 / 2) { }

		/// <summary>
		/// asserts width and height are >= 0
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="w"></param>
		/// <param name="h"></param>
		Rect(int x, int y, int w, int h) :
			X(x), Y(y), width(w), height(h), halfWidth(w / 2), halfHeight(h / 2) {
			assert(width >= 0);
			assert(height >= 0);
		}

		/// <summary>
		/// Make Rect from upper left corner and size.
		/// </summary>
		/// <param name="upperLeftCorner"></param>
		/// <param name="w"></param>
		/// <param name="h"></param>
		Rect(Point upperLeftCorner, int w, int h) :
			X(upperLeftCorner.X), Y(upperLeftCorner.Y), width(w), height(h), halfWidth(w / 2), halfHeight(h / 2) {
			assert(width >= 0);
			assert(height >= 0);
		}

		/// <summary>
		/// Make Rect from size and CENTER POINT.
		/// </summary>
		/// <param name="w"></param>
		/// <param name="h"></param>
		/// <param name="centerPt"></param>
		Rect(int w, int h, Point centerPt) :
			X(centerPt.X - w / 2), Y(centerPt.Y - h / 2), width(w), height(h), halfWidth(w / 2), halfHeight(h / 2) {
			assert(width >= 0);
			assert(height >= 0);
		}

		Rect(cv::Rect& r) :
			X(r.x), Y(r.y), width(r.width), height(r.height), halfWidth(r.width / 2), halfHeight(r.height / 2) {
			assert(width >= 0);
			assert(height >= 0);
		}

		bool Inside(const int x, const int y) {
			return x >= X && x < right() && y >= Y && y < bottom();
		}

		bool Outside(const int x, const int y) {
			return x < X || x >= right() || y < Y&& y >= bottom();
		}

		/// <summary>
		/// Force p to be within the rect. Not valid if width or height is zero. (unchecked)
		/// </summary>
		/// <param name="p"></param>
		/// <returns></returns>
		void Clamp(Point& p) {
			if (p.X < X) p.X = X;
			else if (p.X >= right()) p.X = right() - 1;

			if (p.Y < Y) p.Y = Y;
			else if (p.Y >= bottom()) p.Y = bottom() - 1;
		}

		/// <summary>
		/// Returns a Rect that is inside outer Rect nearest to where this Rect is.
		/// Assumes outerRect is larger than this rect width, height.
		/// </summary>
		/// <param name="outerRect"></param>
		/// <returns></returns>
		Rect ForceInRect(const Rect& outerRect) {
			return Rect(X < outerRect.X ? outerRect.X : X >= outerRect.right() - width ? outerRect.right() - width - 1 : X,
				Y < outerRect.Y ? outerRect.Y : Y >= outerRect.bottom() - height ? outerRect.bottom() - height - 1 : Y,
				width, height);

		}

		void CenterOnInPlace(const Point& p) {
			X = p.X - halfWidth;
			Y = p.Y - halfHeight;
		}

		void CenterOnInPlace(const int x, const int y) {
			X = x - halfWidth;
			Y = y - halfHeight;
		}

		cv::Rect toOpenCVRect() const {
			return cv::Rect(X, Y, width, height);
		}

		wxRect toWxRect() const {
			return wxRect(X, Y, width, height);
		}


	};

}