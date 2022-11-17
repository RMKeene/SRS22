#include "TextOutIO.h"

namespace SRS22 {
	std::mutex TextOutIO::charBufferMutex;
	std::list<TextIOType> TextOutIO::charBuffer;
	bool TextOutIO::wantsClear = false;
	int TextOutIO::maxBufferSize = 1000;

	TextOutIO::TextOutIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	TextOutIO::~TextOutIO() {
	}

	bool TextOutIO::Init() {
		IOCommon::Init();
		return true;
	}

	void TextOutIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void TextOutIO::PreTick() {
		IOCommon::PreTick();
	}

	void TextOutIO::PostTick() {
		IOCommon::PostTick();
	}

	void TextOutIO::UnitTest() {
	}

	/// <summary>
	/// From the Brain to tell this to put a character out.
	/// </summary>
	/// <param name="c"></param>
	void TextOutIO::TakeCharacter(TextIOType c) {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		while (charBuffer.size() > maxBufferSize)
			charBuffer.pop_back();
		charBuffer.push_front(c);
	}

	/// <summary>
	/// From the Brain to tell this to clear the window.
	/// </summary>
	void TextOutIO::ClearTextWindow() {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		wantsClear = true;
	}

	/// <summary>
	/// Where the UI can ask if the Brain wants to output characters to the text window. (TopTextFrame.cpp and .h)
	/// True if there was a character and c was set.
	/// </summary>
	/// <param name="c"></param>
	bool TextOutIO::GetCharacterOut(TextIOType& c) {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		if (charBuffer.size() > 0) {
			c = charBuffer.back();
			charBuffer.pop_back();
			return true;
		}
		return false;
	}

	/// <summary>
	/// Where the UI can ask if the Brain wants the text out window cleared.  (TopTextFrame.cpp and .h)
	/// </summary>
	bool TextOutIO::GetClearOut() {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		if (wantsClear) {
			wantsClear = false;
			return true;
		}
		return false;
	}
}