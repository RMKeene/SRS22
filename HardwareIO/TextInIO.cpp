#include "TextInIO.h"

namespace SRS22 {
	std::mutex TextInIO::charBufferMutex;
	std::list<TextIOType> TextInIO::charBuffer;
	bool TextInIO::receivedClear = false;
	int TextInIO::maxBufferSize = 1000;

	TextInIO::TextInIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	TextInIO::~TextInIO() {
	}

	bool TextInIO::Init() {
		IOCommon::Init();
		return true;
	}

	void TextInIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void TextInIO::PreTick() {
		IOCommon::PreTick();
	}

	void TextInIO::PostTick() {
		IOCommon::PostTick();
	}

	void TextInIO::UnitTest() {
	}

	/// <summary>
	/// Brain can ask if any input characters have come in from the UI and user. (TopTextFrame.cpp and .h)
	/// </summary>
	/// <param name="c"></param>
	bool TextInIO::GetCharacterIn(TextIOType& c) {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		if (charBuffer.size() > 0) {
			c = charBuffer.back();
			charBuffer.pop_back();
			return true;
		}
		return false;
	}

	/// <summary>
	/// Where the Brain can ask if the UI cleared the input text window from the user. (TopTextFrame.cpp and .h)
	/// </summary>
	bool TextInIO::GetClearIn() {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		if (receivedClear) {
			receivedClear = false;
			return true;
		}
		return false;
	}

	/// <summary>
	/// Where the UI can stuff characters that were just entered in the text input window and keyboard.
	/// </summary>
	/// <param name="c"></param>
	void TextInIO::TakeCharacterInput(TextIOType c) {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		while (charBuffer.size() > maxBufferSize)
			charBuffer.pop_back();
		charBuffer.push_front(c);
	}

	/// <summary>
	/// Where the UI can warn that the text windows was cleared.
	/// </summary>
	void TextInIO::TakeClearInput() {
		std::lock_guard<std::mutex> lk(charBufferMutex);
		receivedClear = true;
	}
}