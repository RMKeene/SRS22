#pragma once

/// <summary>
/// In the Brain is the only Tick() method and it is called frequently.
/// Tickable defines the phases of the brain Tick that any object can participate in.
/// 
/// Order of call is PreTick, ComputeNextState, LatchNewState, PostTick, LearningPhase.
/// Within each phase there is no assumption of order of execution.
/// </summary>
class Tickable
{
	public:
		/// <summary>
		/// The hardware IO and UI PreTick for getting external and UI world state.
		/// </summary>
		virtual void PreTickHardwareAndIO() {}
		virtual void ComputeNextState(boolean doParallel) {}
		virtual void LatchNewState(boolean doParallel) {}
		virtual void PostTickHardwareAndUI() {}
		virtual void LearningPhase(boolean doParallel) {}
		
};

