#pragma once
#include "pch.h"

/// <summary>
/// In the Brain is the only Tick() method and it is called frequently.
/// Tickable defines the phases of the brain Tick that any object can participate in.
/// 
/// Order of call is PreTick, ComputeNextState, LatchNewState, PostTick.
/// Within each phase there is no assumption of order of execution.
/// </summary>
class Tickable
{
	public:
		/// <summary>
		/// The hardware IO and UI PreTick for getting external and UI world state.
		/// </summary>
		virtual void PreTickHardwareAndIO() {}
		virtual void ComputeNextState() {}
		virtual void LatchNewState() {}
		virtual void PostTickHardwareAndUI() {}
		virtual void LearningPhase() {}
};

