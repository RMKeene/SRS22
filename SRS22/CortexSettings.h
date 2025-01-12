struct CortexSettings {
	float growthRate = 0.01f;
	/// <summary>
	/// How much energy a neuron gains each tick.
	/// </summary>
	float energyRechargePerTick = 0.02f;
	/// <summary>
	/// If energy falls below this the neuron is changed to disabled. It is too tired.
	/// There is hysteresis here.
	/// </summary>
	float lowEnergyThreshold = 0.1f;
	/// <summary>
	/// If energy is above this then the neuron is changed to enabled.
	/// </summary>
	float highEnergyThreshold = 0.9f;
	/// <summary>
	/// How much energy is subtracted if the neuron fires. This is subtracted each time a link fires, so is often 
	/// subtracted multiple times per tick.
	/// </summary>
	float energyDepletionOnFire = 0.05f / (float)NEURON_UPSTREAM_LINKS;

	/// <summary>
	/// How strongly links matches move the neuron's charge toward L.selfCharge across all weighted votes for next state.
	/// Softened to avoid too much overall energy in the system. 1.0 coffee overdose, 0.0 brain dead.
	/// </summary>
	float connectionThrottle = 0.5f;

	/// <summary>
	/// How quickly "being a match" falls off as actual charge moves away from the NeuronLink selfCharge.
	/// So if this is 10.0 then a 0.1 difference in charge will reduce the match strength to 0.0.
	/// When match strength is 0.0 then the connection is in effect hidden. (See Neural Hiding)
	/// </summary>
	float linkMatchSharpness = 10.0f;

	/// <summary>
	/// If confidence falls below this then a reroute might happen.
	/// </summary>
	float rerouteThreshold = 0.001f;
	/// <summary>
	/// Probability of a reroute on any given tick if confidence is below rerouteThreshold.
	/// </summary>
	float rerouteProbability = 0.01f;
	float lowLearnThreshold = 0.25f;
	float lowLearnRate = 0.01f;
	float hiLearnRate = 0.05f;

	float confidenceAdjustmentUpRate = 1.01f;
	float confidenceAdjustmentDownRate = 0.999f;
	float minimumConfidence = 0.0001f;
	float maximumConfidence = 0.9999f;
	/// <summary>
	/// Initial confidence after a reroute.
	/// </summary>
	float rerouteConfidenceSet = 0.5f;
};