#pragma once

#define IOCOMMON_SETCLASSNAME ioClassName = typeid(*this).name()

namespace SRS22 {
	/// <summary>
	/// Type of characters Text IO deals with. We want UNICODE 16 bit unsigned.
	/// </summary>
	typedef unsigned short TextIOType;

	/// <summary>
	/// All Input and Output, such as camera, screen snapshot-er, audio in, voice out...
	/// go through a IOCommon derived class. The Brain overall system never talks to hardware such as Win32
	/// audio code directly. In general low level hardware classes end in ...Helper, such as WaveOutputHelper.h
	///
	/// Often IOCommon subclasses calculate matricies used by more than one Map for processing.
	/// This tries to reduce recalculation of effects. E.g. previous and
	/// current camera frame low resolution.
	///
	/// IOCommon sub class instances are all registered by class name in a global map, use
	/// static IOCommon* GetIO(const std::string ioClassNm) to get at them. In the Brain creator and Brain::Init the
	/// IOCommons get set up. There are never more than one instance of a IOCommon sub class.
	///
	/// Also see https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
	/// </summary>
	class IOCommon : std::enable_shared_from_this<IOCommon> {
	private:
		static std::map<std::string, IOCommon*>* globalIOTable;
		// Lets us force static global creation order.
		// See  https://isocpp.org/wiki/faq/ctors#static-init-order
		static std::map<std::string, IOCommon*>& getGlobalIOTable() {
			if (!globalIOTable)
				globalIOTable = new std::map<std::string, IOCommon*>();
			return *globalIOTable;
		}

	protected:
		// Treat as const after constructors are done!
		std::string ioClassName;

		/// <summary>
		/// Only sub classes of IOCommon are allowed to be created in outside code.
		/// </summary>
		/// <param name="ioClassName"></param>
		IOCommon();

	public:

		std::string getIOClassName() { return ioClassName; }

		std::shared_ptr<IOCommon> getptr() {
			return shared_from_this();
		}

		~IOCommon();

		/// <summary>
		/// Find the global singleton for a given IOCommon subclass.
		/// NOT reference counted.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="ioClassNm"></param>
		/// <returns></returns>
		template <typename T>
		static T* GetIO() {
			const std::string ioClassNm = typeid(T).name();
			if (getGlobalIOTable().empty()) {
				throw std::logic_error(std::string("Undefined IOCommon uid. (Empty IOCommon table, nothing initialized?) Not allowed. ioClassName=") + ioClassNm);
			}

			auto p = getGlobalIOTable().find(ioClassNm);
			if (p == getGlobalIOTable().end())
				throw std::logic_error(std::string("Undefined IOCommon uid. Not allowed. ioClassName=") + ioClassNm);
			return (T*)p->second;
		}

		virtual bool Init();
		virtual void Shutdown();

		/// <summary>
		/// Called for each IOCommon at the start of tick in Brain.
		/// </summary>
		virtual void PreTickHardwareAndIO();
		/// <summary>
		/// Called for each IOCommon at the end of tick in Brain.
		/// </summary>
		virtual void PostTickHardwareAndUI();

		virtual void UnitTest();
	};
}