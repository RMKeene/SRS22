#pragma once

/// <summary>
/// NEURON_INPUTS is the number of inputs to each neuron. If this changes after a brain save to disk, then on reload
/// the inputs will be truncated if less, and expanded with random connections and weights if more. In a full brain system this 
/// should something like 1000, but for development purposes we can use a smaller number.
/// </summary>
#define NEURON_INPUTS 8

/// <summary>
/// How many Neurons are in the Cortex. Must be larger than the total ConceptMap space at a bare minimum.
/// </summary>
#define TOTAL_NEURONS 600000

/// <summary>
/// In order to avoid memory copies and maximize memory locality, an keep the passes through the entire cortex to a minimum,
/// we keep the charge history (current charge, next charge, charge two ticks ago etc.) in a circular queue.
/// This is how large the history is. Must be at a minimum 2, boing current charge and next charge.
/// </summary>
#define NEURON_HISTORY 3
#define NEURON_HISTORY_MINUS_ONE 2
