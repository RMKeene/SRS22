#pragma once
namespace SRS22 {

	/// <summary>
	/// All Input and Outpout, such as camera, screen snapshot-er, audio in, voice out...
	/// go through a IOCommon derrived class. The Brain overall system never talks to hardware such as Win32 
	/// audio code directly. In general low level hardware classes end in ...Helper, such as WaveOutputHelper.h 
	/// </summary>
	class IOCommon {
	public:
		IOCommon();
		~IOCommon();

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

		virtual void UnitTest();
	};

}