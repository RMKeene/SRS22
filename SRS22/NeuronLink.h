#pragma once

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
	/// When we have this charge we expect the other neuron to be otherCharge in value.
	/// </summary>
	float selfCharge = 0.0f;
	/// <summary>
	/// The index of the target neuron. Or if < 0 then no connection.
	/// </summary>
	int otherIdx = NEURON_LINK_UNCONNECTED;
	/// <summary>
	/// The expected charge of the target neuron if there is a match.
	/// </summary>
	float otherCharge = 0.0f;
	/// <summary>
	/// How much we believe otherCharge and selfCharge to be correct and a valid patter of interest.
	/// </summary>
	float confidence = 0.0f;
	bool wasSelfMatch = false;
};