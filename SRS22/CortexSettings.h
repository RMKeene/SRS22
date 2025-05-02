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

			/// <summary>
			/// Which row in the GUI section for settings this one goes.
			/// </summary>
			int SettingRow = 0;
			std::string Tag;
			std::string Name;
			std::string Description;

			SRSetting(const float f, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::F), Name(name), Description(description), SettingRow(settingRow) {
				SetValue(f);
			}

			SRSetting(const double d, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::D), Name(name), Description(description), SettingRow(settingRow) {
				SetValue(d);
			}

			SRSetting(const int i, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: Tag(tag), Type(SettingType::I), Name(name), Description(description), SettingRow(settingRow) {
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

		class SRSettingF : public SRSetting {
		public:
			SRSettingF(float f, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: SRSetting(f, settingRow, tag, name, description) {
			}

			float operator() () const {
				return F();
			}

			void operator= (float f) {
				Set(f);
			}
		};

		class SRSettingD : public SRSetting {
		public:
			SRSettingD(double d, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: SRSetting(d, settingRow, tag, name, description) {
			}

			double operator() () const {
				return D();
			}

			void operator= (double d) {
				Set(d);
			}
		};

		class SRSettingI : public SRSetting {
		public:
			SRSettingI(int i, const int settingRow, const std::string& tag, const std::string& name, const std::string& description)
				: SRSetting(i, settingRow, tag, name, description) {
			}

			int operator() () const {
				return I();
			}

			void operator= (int i) {
				Set(i);
			}
		};

		/// <summary>
		/// How much a neuron's Charge decays toward 0.0f each tick.
		/// </summary>
		SRSettingF chargeDepletionRate = SRSettingF(getDecayMultiplier(5.0f), 1, "chargeDepletionRate",
			"Charge Depletion Rate", "How much a neuron's Charge decays toward 0.0f each tick.");

		/// <summary>
		/// How much the cortex usable neurons expands per tick.
		/// </summary>
		SRSettingF growthRate = SRSettingF(0.01f, 1, "growthRate",
			"Growth Rate", "How much the cortex usable neurons expands per tick.");

		/// <summary>
		/// How much energy a neuron gains each tick.
		/// </summary>
		SRSettingF energyRechargeRate = SRSettingF(0.02f, 1, "energyRechargeRate",
			"Energy Recharge Rate", "How much energy a neuron gains each tick.");

		/// <summary>
		/// If energy falls below this the neuron is changed to disabled. It is too tired.
		/// </summary>
		SRSettingF lowEnergyThreshold = SRSettingF(0.1f, 1, "lowEnergyThreshold",
			"Low Energy Threshold", "If energy falls below this the neuron is changed to disabled. It is too tired.");

		/// <summary>
		/// If energy is above this then the neuron is changed to enabled.
		/// </summary>
		SRSettingF highEnergyThreshold = SRSettingF(0.9f, 1, "highEnergyThreshold",
			"High Energy Threshold", "If energy is above this then the neuron is changed to enabled.");

		/// <summary>
		/// How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.
		/// </summary>
		SRSettingF energyDepletionOnFire = SRSettingF(0.9f * NEURON_UPSTREAM_LINKS_INVERSE, 1, "energyDepletionOnFire",
			"Energy Depletion On Fire", "How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.");

		/// <summary>
		/// The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.
		/// </summary>
		SRSettingF maxEnergy = SRSettingF(2.0f, 2, "maxEnergy",
			"Max Energy", "The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.");

		/// <summary>
		/// How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)
		/// </summary>
		SRSettingF connectionThrottle = SRSettingF(0.5f, 2, "connectionThrottle",
			"Connection Throttle", "How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)");

		/// <summary>
		/// If confidence falls below this then a reroute might happen.
		/// </summary>
		SRSettingF rerouteThreshold = SRSettingF(0.001f, 2, "rerouteThreshold",
			"Reroute Threshold", "If confidence falls below this then a reroute might happen.");

		/// <summary>
		/// Probability of a reroute on any given tick if confidence is below rerouteThreshold.
		/// </summary>
		SRSettingF rerouteProbability = SRSettingF(0.01f, 2, "rerouteProbability",
			"Reroute Probability", "Probability of a reroute on any given tick if confidence is below rerouteThreshold.");

		/// <summary>
		/// General factor of learning rates speed.
		/// </summary>
		SRSettingF overallLearnRate = SRSettingF(0.05f, 2, "overallLearnRate",
			"Overall Learning Rate", "General factor of learning rates speed.");

		/// <summary>
		/// How much of the link activity is decayed each tick.
		/// </summary>
		SRSettingF linkActivityDecayRate = SRSettingF(getDecayMultiplier(2.0f), 2, "linkActivityDecayRate",
			"Link Activity Decay Rate", "How much of the link activity is decayed each tick.");

		/// <summary>
		/// How much of the link activity is added to the link activity.
		/// </summary>
		SRSettingF linkActivityLearningFactor = SRSettingF(1.1f, 2, "linkActivityLearningFactor",
			"Link Activity Learning Factor", "How much of the link activity is added to the link activity.");

		/// <summary>
		/// How much of input stimulus absolute value is added to L.activity.
		/// </summary>
		SRSettingF linkStimulusToActivityFactor = SRSettingF(0.1f, 2, "linkStimulusToActivityFactor",
			"Link Stimulus to Activity Factor", "How much of input stimulus absolute value is added to L.activity.");

		/// <summary>
		/// How influential the goodness factor of the brain is on learning rate.
		/// </summary>
		SRSettingF learningRateGoodnessFactor = SRSettingF(0.1f, 2, "learningRateGoodnessFactor",
			"Learning Rate Goodness Factor", "How influential the goodness factor of the brain is on learning rate.");

		/// <summary>
		/// Learning rate goes down by the base 2 log of age of the link multiplied by this factor.
		/// </summary>
		SRSettingF learningRateAgeFactor = SRSettingF(1.0f, 2, "learningRateAgeFactor",
			"Learning Rate Age Factor", "Learning rate goes down by the base 2 log of age of the link multiplied by this factor.");

		/// <summary>
		/// General how fast we forget.  Must be <= 1
		/// </summary>
		SRSettingF learningRateForgetFactor = SRSettingF(0.999999f, 3, "learningRateForgetFactor",
			"Learning Rate Forget Factor", "General how fast we forget.  Must be <= 1");

		/// <summary>
		/// How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.
		/// So an pre-offset of 256 ticks is 8.
		/// </summary>
		SRSettingI learningRateForgetLogOffset = SRSettingI(8, 3, "learningRateForgetLogOffset",
			"Learning Rate Forget Log Offset", "How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// 0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago.
		/// Must NOT exceed NEURON_HISTORY - 1.
		/// </summary>
		SRSettingI learningRateTicksOffset = SRSettingI(2, 3, "learningRateTicksOffset",
			"Learning Rate Ticks Offset", "0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago. Must NOT exceed NEURON_HISTORY - 1.");

		/// <summary>
		/// How fast confidence decays over time.
		/// </summary>
		SRSettingF confidenceForgetFactor = SRSettingF(0.999999f, 3, "confidenceForgetFactor",
			"Confidence Forget Factor", "How fast confidence decays over time.");

		/// <summary>
		/// How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.
		/// </summary>
		SRSettingI confidenceForgetLogOffset = SRSettingI(8, 3, "confidenceForgetLogOffset",
			"Confidence Forget Log Offset", "How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// How rapidly confidence increases on a correct stimulus match.
		/// </summary>
		SRSettingF confidenceAdjustmentUpRate = SRSettingF(1.01f, 3, "confidenceAdjustmentUpRate",
			"Confidence Adjustment Up Rate", "How rapidly confidence increases on a correct stimulus match.");

		/// <summary>
		/// If a link match is not correct this is how much confidence decays.
		/// </summary>
		SRSettingF confidenceAdjustmentDownRate = SRSettingF(getDecayMultiplier(200.0f), 3, "confidenceAdjustmentDownRate",
			"Confidence Adjustment Down Rate", "If a link match is not correct this is how much confidence decays.");

		/// <summary>
		/// Confidence can not fall below this level.
		/// </summary>
		SRSettingF minimumConfidence = SRSettingF(0.0001f, 3, "minimumConfidence",
			"Minimum Confidence", "Confidence can not fall below this level.");

		/// <summary>
		/// Confidence can not exceed this level.
		/// </summary>
		SRSettingF maximumConfidence = SRSettingF(0.9999f, 3, "maximumConfidence",
			"Maximum Confidence", "Confidence can not exceed this level.");

		/// <summary>
		/// Initial confidence after a reroute.
		/// </summary>
		SRSettingF rerouteConfidenceSet = SRSettingF(0.5f, 3, "rerouteConfidenceSet",
			"Reroute Confidence Set", "Initial confidence after a reroute.");

	};
}