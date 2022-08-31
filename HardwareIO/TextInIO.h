#pragma once

#include "IOCommon.h"

namespace SRS22 {

	class TextInIO : IOCommon
	{
		static std::mutex charBufferMutex;
		static std::list<char> charBuffer;
		static bool receivedClear;
		static int maxBufferSize;

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

		/// <summary>
		/// Brain can ask if any input characters have come in from the UI and user. (TopTextFrame.cpp and .h)
		/// </summary>
		/// <param name="c"></param>
		static bool GetCharacterIn(char& c);
		/// <summary>
		/// Where the Brain can ask if the UI cleared the input text window from the user. (TopTextFrame.cpp and .h)
		/// </summary>
		static bool GetClearIn();

		/// <summary>
		/// Where the UI can stuff characters that were just entered in the text input window and keyboard.
		/// </summary>
		/// <param name="c"></param>
		static void TakeCharacterInput(char c);
		/// <summary>
		/// Where the UI can warn that the text windows was cleared.
		/// </summary>
		static void TakeClearInput();


		void UnitTest();
	};

}

