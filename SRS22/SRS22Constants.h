#pragma once

// Turns on neuron index, range, and NaN validation.
#define VALIDATE_NEURONS

namespace SRS22 {
	/// <summary>
	/// NEURON_UPSTREAM_LINKS is the number of links from a neuron upstream to other neurons. The neuron tries to predict it's
	/// future state by comparing the upstream neurons charge to the link's otherCharge, for all upstream links.
	/// If they are a close match (and there is high confidence in the link) then the neuron will adjust it's charge to match selfCharge.
	/// In effect we are "comparing a previous state of the entire cortex to the current state and adjusting this neuron's charge to what it was N ticks later.
	/// Thus predicting the future state of this neuron.
	/// 
	/// If this changes after a brain save to disk, then on reload
	/// the inputs will be truncated if less, and expanded with random connections and weights if more. (Not yet implemented)
	/// 
	/// In a full brain system this 
	/// should something like 1000, but for development purposes we can use a smaller number.
	/// </summary>
	constexpr auto NEURON_UPSTREAM_LINKS = 8;
	constexpr auto NEURON_UPSTREAM_LINKS_INVERSE = 1.0f / (float)NEURON_UPSTREAM_LINKS;

	/// <summary>
	/// How many Neurons are in the Cortex. Must be larger than the total ConceptArray space at a bare minimum.
	/// </summary>
	constexpr auto TOTAL_NEURONS = 1600000;

	/// <summary>
	/// In order to be able to predict future states, we need to learn based on previous states.
	/// we keep the charge history (current charge, next charge, charge two ticks ago etc.) in a circular queue.
	/// A circular queue by index so as to never have to do block copies of previous history.
	/// 
	/// This is how large the history is. Must be at a minimum 2, being current charge and next charge.
	/// Must be at least 1 (current tick) + 1 (next tick) + NEURON_HISTORY_MAX_PAST
	/// </summary>
	constexpr auto NEURON_HISTORY = 3;
	constexpr auto NEURON_HISTORY_MAX_PAST = 1;
	constexpr auto NEURON_HISTORY_DEFAULT_PAST_OFFSET = 1;

	/// <summary>
	/// Default is ENABLED.
	/// If a neuron gets fatigued, this goes to DISABLED. (Synaptic Fatigue)
	/// If the neuron is being set by hardware input then this is IS_INPUT and the neuron skips updating state and charge decay and learning etc.
	/// It is a simple state of input from a input ConceptArray.
	/// </summary>
	enum class NeuronType : uint8_t {
		// A Cortex neuron that is neither input nor output. The Regular in "Subsumptive Regular System".
		REGULAR = 0,
		// A Cortex neuron that is an input from hardware or software. It does not learn, nor decay charge.
		// Calculated ArrayTransforms such as FoveaAngle are considered inputs as they are hard coded derrivation from raw inputs.
		IS_INPUT = 2,
		// A Cortex neuron that is an output to hardware or software. It does not fatigue.
		IS_OUTPUT = 3,
	};
}

