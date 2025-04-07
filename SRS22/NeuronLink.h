#pragma once

namespace SRS22 {

	/// If otherIndex is NEURON_LINK_UNCONNECTED then there is no connection.
	constexpr auto NEURON_LINK_UNCONNECTED = -1;

	/// <summary>
	/// A link to an "other" neuron from this neuron with expected value for a 'match'.
	/// When the this neuron is close to the selfCharge, then the target other neuron's 
	/// charge is moved toward the otherCharge value. The amount of movement is determined by confidence and
	/// how close this neuron's charge it to selfCharge.
	/// Since several connections can be active at the same time, the overall effect is a weighted average of all the connections.
	/// The weight is how confident we are.
	/// The overall goal is that the link is predicting this neuron's future state.
	/// </summary>
	struct NeuronLink {
		/// <summary>
		/// When we have a match with otherCharge and upstream neuron's charge, we expect the other neuron to be otherCharge in value.
		/// </summary>
		float weight = 0.0f;
		/// <summary>
		/// The index of the upstream neuron. Or if NEURON_LINK_UNCONNECTED (-1) then no connection.
		/// </summary>
		int otherIdx = NEURON_LINK_UNCONNECTED;
		/// <summary>
		/// How much we believe weight to be correct and a valid pattern of interest.
		/// High confidence (1.0) is a well learned connection. Low confidence (0.001) is a new connection or a connection that is not predicting the future well.
		/// </summary>
		float confidence = 0.0f;
		/// <summary>
		/// How many ticks the link has existed since last reroute.
		/// </summary>
		unsigned long long age = 0;
		/// <summary>
		/// How much the link has been used over quite a few recent ticks.
		/// We add the otherIdx's charge every tick to this value.
		/// Then it decays by settings.LinkActivityDecayRate every tick.
		/// </summary>
		float activity = 0.0f; 

		
	};
}