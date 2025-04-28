namespace SRS22 {


	struct CortexSettings {
	public:
		enum class SettingType { F, D, I };

		class SRSetting {
		public:

			union {
				float f; double d; int i;
			} Value;
			SettingType Type;

			std::string Tag;
			std::string Name;
			std::string Description;

			SRSetting(const float f, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::F), Name(name), Description(description) {
				SetValue(f);
			}

			SRSetting(const double d, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::D), Name(name), Description(description) {
				SetValue(d);
			}

			SRSetting(const int i, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::I), Name(name), Description(description) {
				SetValue(i);
			}

			void SetValue(float value) {
				switch (Type) {
				case SettingType::F:
					Value.f = value;
					break;
				case SettingType::D:
					Value.d = static_cast<double>(value);
					break;
				case SettingType::I:
					Value.i = static_cast<int>(value);
					break;

				}
			}
			float F() const {
				switch (Type) {
				case SettingType::F:
					return Value.f;
				case SettingType::D:
					return static_cast<float>(Value.d);
				case SettingType::I:
					return static_cast<float>(Value.i);
				}
				return 0.0f; // Default case
			}

			double D() const {
				switch (Type) {
				case SettingType::F:
					return static_cast<double>(Value.f);
				case SettingType::D:
					return Value.d;
				case SettingType::I:
					return static_cast<double>(Value.i);
				}
				return 0.0; // Default case
			}

			int I() const {
				switch (Type) {
				case SettingType::F:
					return static_cast<int>(Value.f);
				case SettingType::D:
					return static_cast<int>(Value.d);
				case SettingType::I:
					return Value.i;
				}
				return 0; // Default case
			}

			void Set(float f) {
				switch (Type) {
				case SettingType::F:
					Value.f = f;
					break;
				case SettingType::D:
					Value.d = static_cast<double>(f);
					break;
				case SettingType::I:
					Value.i = static_cast<int>(f);
					break;
				}
			}

			void Set(double d) {
				switch (Type) {
				case SettingType::F:
					Value.f = static_cast<float>(d);
					break;
				case SettingType::D:
					Value.d = d;
					break;
				case SettingType::I:
					Value.i = static_cast<int>(d);
					break;
				}
			}

			void Set(int i) {
				switch (Type) {
				case SettingType::F:
					Value.f = static_cast<float>(i);
					break;
				case SettingType::D:
					Value.d = static_cast<double>(i);
					break;
				case SettingType::I:
					Value.i = i;
					break;
				}
			}
		};

		/// <summary>
		/// How much a neuron's Charge decays toward 0.0f each tick.
		/// </summary>
		SRSetting chargeDepletionRate = SRSetting(getDecayMultiplier(5.0f), "chargeDepletionRate",
			"Charge Depletion Rate", "How much a neuron's Charge decays toward 0.0f each tick.");

		/// <summary>
		/// How much the cortex usable neurons expands per tick.
		/// </summary>
		SRSetting growthRate = SRSetting(0.01f, "growthRate",
			"Growth Rate", "How much the cortex usable neurons expands per tick.");

		/// <summary>
		/// How much energy a neuron gains each tick.
		/// </summary>
		SRSetting energyRechargeRate = SRSetting(0.02f, "energyRechargeRate",
			"Energy Recharge Rate", "How much energy a neuron gains each tick.");

		/// <summary>
		/// If energy falls below this the neuron is changed to disabled. It is too tired.
		/// </summary>
		SRSetting lowEnergyThreshold = SRSetting(0.1f, "lowEnergyThreshold",
			"Low Energy Threshold", "If energy falls below this the neuron is changed to disabled. It is too tired.");

		/// <summary>
		/// If energy is above this then the neuron is changed to enabled.
		/// </summary>
		SRSetting highEnergyThreshold = SRSetting(0.9f, "highEnergyThreshold",	
			"High Energy Threshold", "If energy is above this then the neuron is changed to enabled.");

		/// <summary>
		/// How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.
		/// </summary>
		SRSetting energyDepletionOnFire = SRSetting(0.9f * NEURON_UPSTREAM_LINKS_INVERSE, "energyDepletionOnFire",
			"Energy Depletion On Fire", "How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.");

		/// <summary>
		/// The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.
		/// </summary>
		SRSetting maxEnergy = SRSetting(2.0f, "maxEnergy",
			"Max Energy", "The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.");

		/// <summary>
		/// How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)
		/// </summary>
		SRSetting connectionThrottle = SRSetting(0.5f, "connectionThrottle",
			"Connection Throttle", "How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)");

		/// <summary>
		/// If confidence falls below this then a reroute might happen.
		/// </summary>
		SRSetting rerouteThreshold = SRSetting(0.001f, "rerouteThreshold",
			"Reroute Threshold", "If confidence falls below this then a reroute might happen.");

		/// <summary>
		/// Probability of a reroute on any given tick if confidence is below rerouteThreshold.
		/// </summary>
		SRSetting rerouteProbability = SRSetting(0.01f, "rerouteProbability",
			"Reroute Probability", "Probability of a reroute on any given tick if confidence is below rerouteThreshold.");

		/// <summary>
		/// General factor of learning rates speed.
		/// </summary>
		SRSetting overallLearnRate = SRSetting(0.05f, "overallLearnRate",
			"Overall Learning Rate", "General factor of learning rates speed.");

		/// <summary>
		/// How much of the link activity is decayed each tick.
		/// </summary>
		SRSetting linkActivityDecayRate = SRSetting(getDecayMultiplier(2.0f), "linkActivityDecayRate",
			"Link Activity Decay Rate", "How much of the link activity is decayed each tick.");

		/// <summary>
		/// How much of the link activity is added to the link activity.
		/// </summary>
		SRSetting linkActivityLearningFactor = SRSetting(1.1f, "linkActivityLearningFactor",
			"Link Activity Learning Factor", "How much of the link activity is added to the link activity.");

		/// <summary>
		/// How much of input stimulus absolute value is added to L.activity.
		/// </summary>
		SRSetting linkStimulusToActivityFactor = SRSetting(0.1f, "linkStimulusToActivityFactor",
			"Link Stimulus to Activity Factor", "How much of input stimulus absolute value is added to L.activity.");

		/// <summary>
		/// How influential the goodness factor of the brain is on learning rate.
		/// </summary>
		SRSetting learningRateGoodnessFactor = SRSetting(0.1f, "learningRateGoodnessFactor",
			"Learning Rate Goodness Factor", "How influential the goodness factor of the brain is on learning rate.");

		/// <summary>
		/// Learning rate goes down by the base 2 log of age of the link multiplied by this factor.
		/// </summary>
		SRSetting learningRateAgeFactor = SRSetting(1.0f, "learningRateAgeFactor",
			"Learning Rate Age Factor", "Learning rate goes down by the base 2 log of age of the link multiplied by this factor.");

		/// <summary>
		/// General how fast we forget.  Must be <= 1
		/// </summary>
		SRSetting learningRateForgetFactor = SRSetting(0.999999f, "learningRateForgetFactor",
			"Learning Rate Forget Factor", "General how fast we forget.  Must be <= 1");

		/// <summary>
		/// How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.
		/// So an pre-offset of 256 ticks is 8.
		/// </summary>
		SRSetting learningRateForgetLogOffset = SRSetting(8.0, "learningRateForgetLogOffset",
			"Learning Rate Forget Log Offset", "How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// 0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago.
		/// Must NOT exceed NEURON_HISTORY - 1.
		/// </summary>
		SRSetting learningRateTicksOffset = SRSetting(2, "learningRateTicksOffset",
			"Learning Rate Ticks Offset", "0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago. Must NOT exceed NEURON_HISTORY - 1.");

		/// <summary>
		/// How fast confidence decays over time.
		/// </summary>
		SRSetting confidenceForgetFactor = SRSetting(0.999999f, "confidenceForgetFactor",
			"Confidence Forget Factor", "How fast confidence decays over time.");

		/// <summary>
		/// How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.
		/// </summary>
		SRSetting confidenceForgetLogOffset = SRSetting(8.0f, "confidenceForgetLogOffset",
			"Confidence Forget Log Offset", "How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// How rapidly confidence increases on a correct stimulus match.
		/// </summary>
		SRSetting confidenceAdjustmentUpRate = SRSetting(1.01f, "confidenceAdjustmentUpRate",
			"Confidence Adjustment Up Rate", "How rapidly confidence increases on a correct stimulus match.");

		/// <summary>
		/// If a link match is not correct this is how much confidence decays.
		/// </summary>
		SRSetting confidenceAdjustmentDownRate = SRSetting(getDecayMultiplier(200.0f), "confidenceAdjustmentDownRate",
			"Confidence Adjustment Down Rate", "If a link match is not correct this is how much confidence decays.");

		/// <summary>
		/// Confidence can not fall below this level.
		/// </summary>
		SRSetting minimumConfidence = SRSetting(0.0001f, "minimumConfidence",
			"Minimum Confidence", "Confidence can not fall below this level.");
		
		/// <summary>
		/// Confidence can not exceed this level.
		/// </summary>
		SRSetting maximumConfidence = SRSetting(0.9999f, "maximumConfidence",
			"Maximum Confidence", "Confidence can not exceed this level.");

		/// <summary>
		/// Initial confidence after a reroute.
		/// </summary>
		SRSetting rerouteConfidenceSet = SRSetting(0.5f, "rerouteConfidenceSet",
			"Reroute Confidence Set", "Initial confidence after a reroute.");

	};
}