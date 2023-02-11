#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

namespace SRS22 {
	/// <summary>
	/// A brain part that can have a location in 3D space in a Brain.
	/// An immutable class.
	///
	/// This is the inverted ⅄ connectivity triple mentioned in the paper.
	/// We assume all neurons in a CortexChunk or Concept map have
	/// the same location for connectivity distance purposes.
	/// See paper Connectivity Triples ⅄, and Brain maxNearDistance and minFarDistance
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