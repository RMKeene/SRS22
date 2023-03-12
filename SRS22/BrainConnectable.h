#pragma once
#include "pch.h"

namespace SRS22 {
	/// <summary>
	/// Either a ConceptMap or a CortexChunk that has some array of charges that can be read or written
	/// such that one deoes not have to know which class the target is. 
	/// 
	/// A LinearOffset is a single integer offset in the charge array (M) of the target. E.g. a 3D ConceptMap X,Y,Z converted to
	/// a single linear offset.
	/// 
	/// 
	/// </summary>
	class BrainConnectable
	{
	public:
		virtual int GetRandomLinearOffset() = 0;

		/// <summary>
		/// Get charge from current state.
		/// </summary>
		/// <param name="linearOffset"></param>
		/// <returns></returns>
		virtual float GetChargeValue(const int linearOffset) = 0;
		/// <summary>
		/// Set charge in next state.
		/// </summary>
		/// <param name="linearOffset"></param>
		/// <param name="c"></param>
		/// <returns></returns>
		virtual void SetChargeValue(const int linearOffset, const float c) = 0;
		/// <summary>
		/// Add to charge in next state.
		/// </summary>
		/// <param name="linearOffset"></param>
		/// <param name="c"></param>
		/// <returns></returns>		
		virtual void AddToChargeValue(const int linearOffset, const float c) = 0;

		/// <summary>
		/// Always true for CortexChunks.
		/// Usually true for ConceptMaps. 
		/// If false then a PatternConnection should never be made to this ConceptMap. 
		/// Very low level maps (e.g. Camera raw input) are not directly connectable. 
		/// More abstract maps like CameraFoveaAngle are connectable.
		/// </summary>
		bool isConnectableFlag = true;
	};

}

