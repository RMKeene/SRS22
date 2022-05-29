#pragma once
#include "Point.h"
namespace SRS22 {

	class Rect {
	public:
		int minX;
		int minY;
		int width;
		int height;

		Rect() : minX(0), minY(0), width(0), height(0) {}

		/// <summary>
		/// If width is negative, moves x to x - w, and then negates w.
		/// Same for y and height.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="w"></param>
		/// <param name="h"></param>
		Rect(int x, int y, int w, int h) :
			minX(x), minY(y), width(w), height(h) {
			if (w < 0) {
				x = x - w;
				w = -w;
			}
			if (h < 0) {
				y = y - w;
				w = -w;
			}
		}

		bool Inside(int x, int y) {
			return x >= minX && x < minX + width && y >= minY && y < minY + height;
		}

		bool Outside(int x, int y) {
			return x < minX || x >= minX + width || y < minY&& y >= minY + height;
		}

		/// <summary>
		/// Force p to be within the rect. Not valid if width or height is zero. (unchecked)
		/// </summary>
		/// <param name="p"></param>
		/// <returns></returns>
		void Clamp(Point& p) {
			if (p.X < minX) p.X = minX;
			else if (p.X >= minX + width) p.X = minX + width - 1;
			if (p.Y < minY) p.Y = minY;
			else if (p.Y >= minY + height) p.Y = minY + height - 1;
		}
	};

}