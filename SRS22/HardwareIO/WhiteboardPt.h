#pragma once
#include "../pch.h"

struct WhiteboardPt {
public:
	/// <summary>
	/// 0.0 to 1.0 range of draw surface width.
	/// </summary>
	float x;
	/// <summary>
	/// 0.0 to 1.0 range of draw surface height.
	/// </summary>
	float y;
	/// <summary>
	/// 0.0 means no draw, 1.0 is full draw, 0.5 is half SRC and half DST.
	/// </summary>
	float blend;
	/// <summary>
	/// 0 to 255 Red component.
	/// </summary>
	unsigned char r;
	/// <summary>
	/// 0 to 255 Green component.
	/// </summary>
	unsigned char g;
	/// <summary>
	/// 0 to 255 Blue component.
	/// </summary>
	unsigned char b;

	const unsigned char ChargeToColorUByte(const float vZeroToOne)
	{
		return static_cast<unsigned char>(std::clamp(vZeroToOne * 255.0f, 0.0f, 255.0f));
	}

	const unsigned char ColorUByteToCharge(const unsigned char pixel0To255)
	{
		return static_cast<unsigned char>(std::clamp((float)pixel0To255 / 255.0f, 0.0f, 1.0f));
	}

	WhiteboardPt() :
		r(0), g(0), b(0),
		blend(0.0f),
		x(0.0f), y(0.0f)
	{
	}


	WhiteboardPt(float rCharge, float gCharge, float bCharge, float blendCharge, float xCharge, float yCharge) :
		r(ChargeToColorUByte(rCharge)), g(ChargeToColorUByte(gCharge)), b(ChargeToColorUByte(bCharge)),
		blend(blendCharge),
		x(xCharge), y(yCharge)
	{
	}
};