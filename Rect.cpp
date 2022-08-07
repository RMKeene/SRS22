#include "pch.h"
#include "Rect.h"

namespace SRS22 {

	void Rect::CenterOnInPlace(const int x, const int y) {
		X = x - halfWidth;
		Y = y - halfHeight;
	}

}