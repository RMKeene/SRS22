#pragma once
#include <unordered_map>
#include <string>

namespace SRS22 {

	/// <summary>
	/// We want the Cortex to have one huge linear array of neurons.  Each ConceptMap then deals with some block in the Cortex.
	/// So we want to start at index zero in the Cortex neurons array and declare block that do not overlap.
	/// This class declares the start and end of each ConceptMap explicitly, can be saved to disk, and keeps things from moving around between saves.
	/// </summary>
	class IOMapToContext {
	public:
		/// <summary>
		/// The string is the ConceptMap name, the pair is the start and size in the Cortex neurons array.
		/// The indicies are in Neurons, not bytes.
		/// </summary>
		std::unordered_map<std::string, std::pair<int, int>> map;

		IOMapToContext() {

		}

		/// <summary>
		/// Not thread safe.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="size">Size in Neurons.</param>
		/// <returns>The start of the reserved block and the end + 1 (start of next reserve block).</returns>
		std::pair<int, int> addMapping(std::string name, int size) {
			int start = currentOffset;
			currentOffset += size;
			map[name] = std::make_pair(start, size);
			return map[name];
		}

	private:
		int currentOffset = 0;
	};


}