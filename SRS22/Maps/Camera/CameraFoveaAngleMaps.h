#pragma once
#include "../../ConceptMap.h"

#define CameraFoveaMap_Width 15
#define CameraFoveaMap_Height 15

/// <summary>
/// Concept Maps of the angle of the camera central fovea. E.g. edges slopes.
/// Zero degrees is to the right (+X) on the camera. 90 degrees is to the botton (+Y) on the camera.
/// 45 degrees is to the bottom right (+X, +Y) on the camera.
/// Reverse angles are the same, so 0 is the same as 180, 45 is the same as 225, etc.
/// We use 22.5 degree increments. So the ranges is from 0 to 157.5 degrees.
/// Map Tokens CAMERAFOVEAANGLE000_MAP through CAMERAFOVEAANGLE1575_MAP
/// </summary>
namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 0 deg.
	/// </summary>
	class CameraFoveaAngleMap000 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap000(Brain* br);
		~CameraFoveaAngleMap000();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 22.5 deg.
	/// </summary>
	class CameraFoveaAngleMap225 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap225(Brain* br);
		~CameraFoveaAngleMap225();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	///	Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 45 deg.
	/// </summary>
	class CameraFoveaAngleMap450 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap450(Brain* br);
		~CameraFoveaAngleMap450();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 67.5 deg.
	/// </summary>
	class CameraFoveaAngleMap675 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap675(Brain* br);
		~CameraFoveaAngleMap675();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 90 deg.
	/// </summary>
	class CameraFoveaAngleMap900 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap900(Brain* br);
		~CameraFoveaAngleMap900();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 112.5 deg.
	/// </summary>
	class CameraFoveaAngleMap1125 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap1125(Brain* br);
		~CameraFoveaAngleMap1125();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	///	Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 135 deg.
	/// </summary>
	class CameraFoveaAngleMap1350 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap1350(Brain* br);
		~CameraFoveaAngleMap1350();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 157.5 deg.
	/// </summary>
	class CameraFoveaAngleMap1575 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap1575(Brain* br);
		~CameraFoveaAngleMap1575();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
