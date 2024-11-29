#pragma once

// Turns on neuron index, range, and NaN validation.
//#define VALIDATE_NEURONS

/// <summary>
/// NEURON_OUTPUTS is the number of output NeuronLinks from each neuron to other neurons that try to predict the 
/// future state of the other target Neuron. If this changes after a brain save to disk, then on reload
/// the inputs will be truncated if less, and expanded with random connections and weights if more. In a full brain system this 
/// should something like 1000, but for development purposes we can use a smaller number.
/// </summary>
constexpr auto NEURON_OUTPUTS = 8;

/// <summary>
/// How many Neurons are in the Cortex. Must be larger than the total ConceptMap space at a bare minimum.
/// </summary>
constexpr auto TOTAL_NEURONS = 600000;

/// <summary>
/// In order to avoid memory copies and maximize memory locality, an keep the passes through the entire cortex to a minimum,
/// we keep the charge history (current charge, next charge, charge two ticks ago etc.) in a circular queue.
/// This is how large the history is. Must be at a minimum 2, being current charge and next charge.
/// </summary>
constexpr auto NEURON_HISTORY = 3;
constexpr auto NEURON_HISTORY_MINUS_ONE = NEURON_HISTORY - 1;
