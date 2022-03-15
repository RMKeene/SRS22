#pragma once
namespace SRS22 {

	class IOCommon {
	public:
		IOCommon();
		~IOCommon();

		virtual bool Init();
		virtual void Shutdown();
	};

}