#pragma once

#include "IOCommon.h"

namespace SRS22 {
	class TextInIO : IOCommon
	{
	public:
		TextInIO();
		~TextInIO();

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTick();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTick();

		void UnitTest();
	};

}

