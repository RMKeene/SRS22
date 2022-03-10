#pragma once
#include "pch.h"
#include "ClassPredefines.h"
#include "tinyfloat.h"

namespace SRS22 {

	class ConceptState
	{
	public:

		std::shared_ptr<float> charges;

		const int dims;
		const int w;
		const int h;
		const int d;
		/// <summary>
		/// Size in floats (number of neuron states)
		/// </summary>
		const int size;
		const int bytesize;
		const int wh;

		ConceptState(int w);
		ConceptState(int w, int h);
		ConceptState(int w, int h, int d);
		~ConceptState();

		float get(int x);
		float get(int x, int y);
		float get(int x, int y, int z);
		void put(float v, int x);
		void put(float v, int x, int y);
		void put(float v, int x, int y, int z);

		float Compare(std::shared_ptr<ConceptState> other, const int skip = 1);
	};

}
