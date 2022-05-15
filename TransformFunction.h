#pragma once
#include "pch.h"
#include "ClassPredefines.h"

namespace SRS22 {

	class TransformFunction
	{
	public:
		virtual void Process();
	};

	class BlankTransformFunction : public TransformFunction {
	public:
		void Process() {}
	};
}
