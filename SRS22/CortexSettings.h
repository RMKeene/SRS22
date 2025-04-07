namespace SRS22 {
	struct CortexSettings {
		/// <summary>
		/// How much a neuron's Charge decays toward 0.0f each tick.
		/// </summary>
		float chargeDepletionRate = getDecayMultiplier(5.0f);

		/// <summary>
		/// How much the cortex usable neurons expands per tick.
		/// </summary>
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
		/// How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.
		/// </summary>
		float energyDepletionOnFire = 0.9f * NEURON_UPSTREAM_LINKS_INVERSE;
		/// <summary>
		/// The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.
		/// </summary>
		float maxEnergy = 2.0f;

		/// <summary>
		/// How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.
		/// </summary>
		float connectionThrottle = 0.5f;

		/// <summary>
		/// If confidence falls below this then a reroute might happen.
		/// </summary>
		float rerouteThreshold = 0.001f;
		/// <summary>
		/// Probability of a reroute on any given tick if confidence is below rerouteThreshold.
		/// </summary>
		float rerouteProbability = 0.01f;
		float overallLearnRate = 0.05f;

		float linkActivityDecayRate = getDecayMultiplier(2.0f);
		float linkActivityLearningFactor = 1.1f;

		/// <summary>
		/// How influential the goodness factor of the brain is on learning rate.
		/// </summary>
		float learningRateGoodnessFactor = 0.1f;		
		/// <summary>
		/// Learning rate goes down by the base 2 log of age of the link multiplied by this factor.
		/// </summary>
		float learningRateAgeFactor = 1.0f;

		float confidenceAdjustmentUpRate = 1.01f;
		float confidenceAdjustmentDownRate = getDecayMultiplier(200.0f);
		float minimumConfidence = 0.0001f;
		float maximumConfidence = 0.9999f;
		/// <summary>
		/// Initial confidence after a reroute.
		/// </summary>
		float rerouteConfidenceSet = 0.5f;
	};
}