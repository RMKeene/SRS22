#pragma once

namespace SRS22 {

	/// If otherIndex is NEURON_LINK_UNCONNECTED then there is no connection.
	constexpr auto NEURON_LINK_UNCONNECTED = -1;

	/// <summary>
	/// A link from an "other" upstream  neuron to this neuron with a weight (weight range -1.0 to 1.0).
	/// The overall goal is that the link is predicting this neuron's future state.
	/// </summary>
	struct NeuronLink {
		/// <summary>
		/// Stimulation int this tick to this neuron is Neuron::Charge * Link::weight.
		/// This is adjusted according to how well this neuron was predicted this tick by this Link.
		/// The neuron is threshold at 0.5 so below 0.5 is "off" and above 0.5 is "on".
		/// We then look at the upstream neurons charge N ticks ago. If the upstream charge was high
		/// and this neuron is now above 0.5, this neuron needed more stimulus and the weight is adjusted upward.
		/// If the upstream neuron was high and this neuron is now below 0.5, then this neuron needed inhibition 
		/// and the weight is adjusted downward.
		/// In addition the amount the weight is adjusted less for larger age for the link.
		/// </summary>
		float weight = 0.0f;
		/// <summary>
		/// The index of the upstream neuron. Or if NEURON_LINK_UNCONNECTED (-1) then no connection.
		/// </summary>
		int otherIdx = NEURON_LINK_UNCONNECTED;
		/// <summary>
		/// How much we believe weight to be correct and a valid predictor of the future N ticks in advance.
		/// N is usually 1 or 2 ticks in advance.
		/// 
		/// A "match" is when the upstream neuron is active and this neuron is either near 1.0 charge, or near 0.0 charge
		/// and the weight is positive or negative respectively.
		/// 
		/// High confidence (1.0) is a well learned connection. 
		/// Low confidence (0.001) is a new connection or a connection that is not predicting the future well.
		/// Every time we get a "match" confidence increases by some amount.
		/// Every tick the confidence decays a little bit.
		/// As the Link gets more mature, older, larger age, the confidence changes slower.
		/// If confidence and weight both get very close to zero, the the link is marked unconnected (reaped)
		/// and will soon reroute to a new neuron that is not this neuron or any of its links.
		/// </summary>
		float confidence = 0.0f;
		/// <summary>
		/// How many ticks the link has existed since last reroute.
		/// </summary>
		unsigned long long age = 0;
		
		/// <summary>
		/// Every tick we add the abs(stimulus) to the activity.
		/// Then it decays over a CortexSettings::linkActivityLearningFactor. Active neurons learn faster.
		/// </summary>
		float activity = 0.5f;
	};
}