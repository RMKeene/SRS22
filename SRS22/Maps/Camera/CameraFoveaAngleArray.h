#pragma once
#include "../../ConceptArray.h"

#define CameraFoveaArray_Width 15
#define CameraFoveaArray_Height 15

/// <summary>
/// Concept Maps of the angle of the camera central fovea. E.g. edges slopes.
/// Zero degrees is to the right (+X) on the camera. 90 degrees is to the bottom (+Y) on the camera.
/// 45 degrees is to the bottom right (+X, +Y) on the camera.
/// Reverse angles are the same, so 0 is the same as 180, 45 is the same as 225, etc.
/// We use 22.5 degree increments. So the ranges is from 0 to 157.5 degrees.
/// Map Tokens CAMERAFOVEAANGLE000_MAP through CAMERAFOVEAANGLE1575_MAP
/// </summary>
namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 0 deg.
	/// </summary>
	class CameraFoveaAngleArray000 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray000(Brain* br);
		~CameraFoveaAngleArray000();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 22.5 deg.
	/// </summary>
	class CameraFoveaAngleArray225 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray225(Brain* br);
		~CameraFoveaAngleArray225();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	///	Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 45 deg.
	/// </summary>
	class CameraFoveaAngleArray450 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray450(Brain* br);
		~CameraFoveaAngleArray450();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 67.5 deg.
	/// </summary>
	class CameraFoveaAngleArray675 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray675(Brain* br);
		~CameraFoveaAngleArray675();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 90 deg.
	/// </summary>
	class CameraFoveaAngleArray900 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray900(Brain* br);
		~CameraFoveaAngleArray900();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 112.5 deg.
	/// </summary>
	class CameraFoveaAngleArray1125 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray1125(Brain* br);
		~CameraFoveaAngleArray1125();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	///	Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 135 deg.
	/// </summary>
	class CameraFoveaAngleArray1350 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray1350(Brain* br);
		~CameraFoveaAngleArray1350();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 157.5 deg.
	/// </summary>
	class CameraFoveaAngleArray1575 : public ConceptArray
	{
	public:
		CameraFoveaAngleArray1575(Brain* br);
		~CameraFoveaAngleArray1575();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
