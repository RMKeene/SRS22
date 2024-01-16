#pragma once
#include "ClassPredefines.h"

namespace SRS22 {
	class TransformFunction : std::enable_shared_from_this<TransformFunction>
	{
	public:
		std::shared_ptr<TransformFunction> getptr() {
			return shared_from_this();
		}

		virtual void Process();
	};

	class BlankTransformFunction : public TransformFunction {
	public:
		void Process() {}
	};
}
