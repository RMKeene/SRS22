#pragma once

/// <summary>
/// NEURON_INPUTS is the number of inputs to each neuron. If this changes after a brain save to disk, then on reload
/// the inputs will be truncated if less, and expanded with random connections and weights if more. In a full brain system this 
/// should something like 1000, but for development purposes we can use a smaller number.
/// </summary>
#define NEURON_INPUTS 50

/// <summary>
/// How many Neurons are in the Cortex. Must be larger than the total ConceptMap space at a bare minimum.
/// </summary>
#define TOTAL_NEURONS 700000

/// <summary>
/// In order to avoid memory copies and maximize memory locality, an keep the passes throught the entire cortex to a minimum,
/// we kee the charge history (currnet charge, next charge, charge two ticks ag etc.) in a circular queue.
/// This is how large the history is. Must be at a minimum 2, boing current charge and next charge.
/// </summary>
#define NEURON_HISTORY 3
#define NEURON_HISTORY_MINUS_ONE 2

/// <summary>
/// What the stimulation sum of input matches is divided by to get the actual total to sum in.
/// Approximately NEURON_INPUTS plus a little to soften the effect of a match.
/// </summary> 
#define NEURON_MATCH_SOFTNESS 60.0f

/// <summary>
/// If we are getting an input match, stimulate the target but soften by this amount.
#define NEURON_TARGET_STIMULATION_FACTOR 0.1f