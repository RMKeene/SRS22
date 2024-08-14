#pragma once
#include "../../ConceptMap.h"

#define CameraFoveaMap_Width 15
#define CameraFoveaMap_Height 15

/// <summary>
/// Map Tokens CAMERAFOVEAANGLE000_MAP through CAMERAFOVEAANGLE1575_MAP
/// </summary>
namespace SRS22 {
	/// <summary>
	/// Raw pixel map of center of camera fovea in color. 8x8 in the center of the ScreenAttnSpot. Angle 0 deg.
	/// </summary>
	class CameraFoveaAngleMap000 : public ConceptMap
	{
	public:
		CameraFoveaAngleMap000(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap225(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap450(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap675(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap900(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap1125(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap1350(Brain* br, bool computeNextStateEnabled = true);
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
		CameraFoveaAngleMap1575(Brain* br, bool computeNextStateEnabled = true);
		~CameraFoveaAngleMap1575();

		virtual void ComputeNextState(boolean doParallel) override;
		virtual void LatchNewState(boolean doParallel) override;
	};

}
