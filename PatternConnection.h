#pragma once
#include "pch.h"
#include "ClassPredefines.h"

namespace SRS22 {
	/// <summary>
	/// A single input or output connection in a Pattern to some point in the Brain. 
	/// Can connect to either ConceptMaps or CortexChunks. In effect a pointer to anywhere in the Brain.
	/// </summary>
	class PatternConnection
	{
	public:
		BrainConnectable * target;
		/// <summary>
		/// Linear index in map.M.charges or map.NextM.charges or CortexChunk
		/// </summary>
		int linearOffset;
		float ExpectedCharge;

		PatternConnection(BrainConnectable* target, int linearOffset);

		/// <summary>
		/// A.linearOffset == B.linearOffset && A.target == B.target
		/// 
		/// Checkes linearOffset first for speed as that is much more likely to be unequal.
		/// </summary>
		/// <param name="A"></param>
		/// <param name="B"></param>
		/// <returns></returns>
		inline static bool equals(const PatternConnection& A, const PatternConnection& B) {
			return A.linearOffset == B.linearOffset && A.target == B.target;
		}

		inline static bool equals(const PatternConnection& A, const BrainConnectable* Btarget, const int Boffset) {
			return A.linearOffset == Boffset && A.target == Btarget;
		}

		/// <summary>
		/// A.linearOffset != B.linearOffset || A.target != B.target
		/// 
		/// Checkes linearOffset first for speed as that is much more likely to be unequal.
		/// </summary>
		/// <param name="A"></param>
		/// <param name="B"></param>
		/// <returns></returns>
		inline static bool unequals(const PatternConnection& A, const PatternConnection& B) {
			return A.linearOffset != B.linearOffset || A.target != B.target;
		}

		inline static bool unequals(const PatternConnection& A, const BrainConnectable* Btarget, const int Boffset) {
			return A.linearOffset != Boffset || A.target != Btarget;
		}
	};
}
