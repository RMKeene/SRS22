#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "BrainLocatable.h"

namespace SRS22 {
	/// <summary>
	/// A 2D planar rectangle of Cortex pattern matching neurons.
	/// </summary>
	class CortexChunk : public BrainLocatable
	{
	public:
		CortexChunk(const cv::Vec3f location) : BrainLocatable(location) {

		}

	};

}