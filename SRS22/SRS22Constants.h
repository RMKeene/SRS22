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