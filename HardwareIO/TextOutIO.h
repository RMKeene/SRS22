#pragma once

#include "IOCommon.h"

namespace SRS22 {

	/// <summary>
	/// Text out to the text output window.
	/// </summary>
	class TextOutIO : IOCommon
	{
		static std::mutex charBufferMutex;
		static std::list<char> charBuffer;
		static bool wantsClear;

		static int maxBufferSize;

	public:
		TextOutIO();
		~TextOutIO();

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

		/// <summary>
		/// From the Brain to tell this to put a character out.
		/// </summary>
		/// <param name="c"></param>
		static void TakeCharacter(char c);

		/// <summary>
		/// From the Brain to tell this to clear the window.
		/// </summary>
		static void ClearTextWindow();

		/// <summary>
		/// Where the UI can ask if the Brain wants to output characters to the text window. (TopTextFrame.cpp and .h)
		/// True if there was a character and c was set.
		/// </summary>
		/// <param name="c"></param>
		static bool GetCharacterOut(char& c);
		/// <summary>
		/// Where the UI can ask if the Brain wants the text out window cleared.  (TopTextFrame.cpp and .h)
		/// </summary>
		static bool GetClearOut();

		void UnitTest();
	};
}

