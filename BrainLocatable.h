#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

namespace SRS22 {
	/// <summary>
	/// A brain part that can have a location in 3D space in a Brain.
	/// An immutable class.
	///
	/// Ranges of x, y, z are 0.0 to 1.0. Lower Z are more concrete, higher z is more abstract. 
	/// x,y defines general concept categories.
	/// </summary>
	class BrainLocatable
	{
	public:
		/// <summary>
		/// Brain location, 3D. Concept relevance location.
		/// </summary>
		const cv::Vec3f location;

		BrainLocatable(const cv::Vec3f location) : location(location) {
		}
	};
}