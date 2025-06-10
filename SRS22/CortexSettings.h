#pragma once
#include "SRS22pch.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "SRSMath.h"

namespace SRS22 {

	struct CortexSettings {
	public:
		enum class SettingType { F, D, I };

		class SRSSetting {
		public:


			typedef union {
				float f;
				double d;
				int i;
			} SRSSettingValue;


			SRSSettingValue Value;
			SRSSettingValue OriginalValue;
			const SRSSettingValue DefaultValue;
			SRSSettingValue PreviousValue;

			SettingType Type;

			int SettingRow = 0;
			std::string Tag;
			std::string Name;
			std::string Description;
			std::string UILabel;
			/// <summary>
			/// Used by the UI to hook in the UI element to the setting->
			/// </summary>
			void* clientData = nullptr;

			SRSSetting(float f, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: Tag(tag), Type(SettingType::F), Name(name), Description(description), SettingRow(settingRow),
				Value({ .f = f }), OriginalValue({ .f = f }), DefaultValue({ .f = f }), PreviousValue({ .f = f }),
				UILabel(uiLabel)
			{
			}

			SRSSetting(double d, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: Tag(tag), Type(SettingType::D), Name(name), Description(description), SettingRow(settingRow),
				Value({ .d = d }), OriginalValue({ .d = d }), DefaultValue({ .d = d }), PreviousValue({ .d = d }),
				UILabel(uiLabel)
			{
			}

			SRSSetting(int i, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: Tag(tag), Type(SettingType::I), Name(name), Description(description), SettingRow(settingRow),
				Value({ .i = i }), OriginalValue({ .i = i }), DefaultValue({ .i = i }), PreviousValue({ .i = i }),
				UILabel(uiLabel)
			{
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
				return 0.0f;
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
				return 0.0;
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
				return 0;
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

		class SRSettingF : public SRSSetting {
		public:
			SRSettingF(float f, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: SRSSetting(f, settingRow, tag, name, uiLabel, description) {
			}

			inline float operator() () const {
				return Value.f;
			}

			void operator= (float f) {
				Set(f);
			}
		};

		class SRSettingD : public SRSSetting {
		public:
			SRSettingD(double d, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: SRSSetting(d, settingRow, tag, name, uiLabel, description) {
			}

			inline double operator() () const {
				return Value.d;
			}

			void operator= (double d) {
				Set(d);
			}
		};

		class SRSettingI : public SRSSetting {
		public:
			SRSettingI(int i, int settingRow, std::string tag, std::string name, std::string uiLabel, std::string description)
				: SRSSetting(i, settingRow, tag, name, uiLabel, description) {
			}

			inline int operator() () const {
				return Value.i;
			}

			void operator= (int i) {
				Set(i);
			}
		};

		/// <summary>
		/// How much a neuron's Charge decays toward 0.0f each tick.
		/// </summary>
		SRSettingF chargeDepletionRate = SRSettingF(0.12f, 0, std::string("chargeDepletionRate"),
			"Charge Depletion Rate",
			"CgDepRt",
			"How much a neuron's Charge decays toward 0.0f each tick.");

		/// <summary>
		/// How much the cortex usable neurons expands per tick.
		/// </summary>
		SRSettingF growthRate = SRSettingF(0.01f, 0, "growthRate",
			"Growth Rate",
			"GrwRt",
			"How much the cortex usable neurons expands per tick.");

		/// <summary>
		/// How much energy a neuron gains each tick.
		/// </summary>
		SRSettingF energyRechargeRate = SRSettingF(0.02f, 0, "energyRechargeRate",
			"Energy Recharge Rate",
			"EnrRchRt",
			"How much energy a neuron gains each tick.");

		/// <summary>
		/// If energy falls below this the neuron is changed to disabled. It is too tired.
		/// </summary>
		SRSettingF lowEnergyThreshold = SRSettingF(0.1f, 0, "lowEnergyThreshold",
			"Low Energy Threshold",
			"LowEngThr",
			"If energy falls below this the neuron is changed to disabled. It is too tired.");

		/// <summary>
		/// If energy is above this then the neuron is changed to enabled.
		/// </summary>
		SRSettingF highEnergyThreshold = SRSettingF(0.9f, 0, "highEnergyThreshold",
			"High Energy Threshold",
			"HighEngThr",
			"If energy is above this then the neuron is changed to enabled.");

		/// <summary>
		/// How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.
		/// </summary>
		SRSettingF energyDepletionOnFire = SRSettingF(0.9f * NEURON_UPSTREAM_LINKS_INVERSE, 0, "energyDepletionOnFire",
			"Energy Depletion On Fire",
			"EnrDplOnFire",
			"How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.");

		/// <summary>
		/// The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.
		/// </summary>
		SRSettingF maxEnergy = SRSettingF(2.0f, 0, "maxEnergy",
			"Max Energy",
			"MaxEngy",
			"The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.");

		/// <summary>
		/// How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)
		/// </summary>
		SRSettingF connectionThrottle = SRSettingF(0.5f, 0, "connectionThrottle",
			"Connection Throttle",
			"ConnThrtl",
			"How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)");

		/// <summary>
		/// If confidence falls below this then a reroute might happen.
		/// </summary>
		SRSettingF rerouteThreshold = SRSettingF(0.001f, 0, "rerouteThreshold",
			"Reroute Threshold",
			"RertThr",
			"If confidence falls below this then a reroute might happen.");

		/// <summary>
		/// Probability of a reroute on any given tick if confidence is below rerouteThreshold.
		/// </summary>
		SRSettingF rerouteProbability = SRSettingF(0.01f, 1, "rerouteProbability",
			"Reroute Probability",
			"RertProb",
			"Probability of a reroute on any given tick if confidence is below rerouteThreshold.");

		/// <summary>
		/// General factor of learning rates speed.
		/// </summary>
		SRSettingF overallLearnRate = SRSettingF(0.05f, 1, "overallLearnRate",
			"Overall Learning Rate",
			"OvallLrnRt",
			"General factor of learning rates speed.");

		/// <summary>
		/// How much of the link activity is decayed each tick.
		/// </summary>
		SRSettingF linkActivityDecayRate = SRSettingF(getDecayMultiplier(2.0f), 1, "linkActivityDecayRate",
			"Link Activity Decay Rate",
			"LnkActvDcyRt",
			"How much of the link activity is decayed each tick.");

		/// <summary>
		/// How much of the link activity is added to the link activity.
		/// </summary>
		SRSettingF linkActivityLearningFactor = SRSettingF(1.1f, 1, "linkActivityLearningFactor",
			"Link Activity Learning Factor",
			"LnkActvLrnRt",
			"How much of the link activity is added to the link activity.");

		/// <summary>
		/// How much of input stimulus absolute value is added to L.activity.
		/// </summary>
		SRSettingF linkStimulusToActivityFactor = SRSettingF(0.1f, 1, "linkStimulusToActivityFactor",
			"Link Stimulus to Activity Factor",
			"LnkStmToActvFctr",
			"How much of input stimulus absolute value is added to L.activity.");

		/// <summary>
		/// How influential the goodness factor of the brain is on learning rate.
		/// </summary>
		SRSettingF learningRateGoodnessFactor = SRSettingF(0.1f, 1, "learningRateGoodnessFactor",
			"Learning Rate Goodness Factor",
			"LrnRtGdFctr",
			"How influential the goodness factor of the brain is on learning rate.");

		/// <summary>
		/// Learning rate goes down by the base 2 log of age of the link multiplied by this factor.
		/// </summary>
		SRSettingF learningRateAgeFactor = SRSettingF(1.0f, 1, "learningRateAgeFactor",
			"Learning Rate Age Factor",
			"LrnRtAgeFctr",
			"Learning rate goes down by the base 2 log of age of the link multiplied by this factor.");

		/// <summary>
		/// General how fast we forget.  Must be <= 1
		/// </summary>
		SRSettingF learningRateForgetFactor = SRSettingF(0.999999f, 1, "learningRateForgetFactor",
			"Learning Rate Forget Factor",
			"LrnRtFrgtFctr",
			"General how fast we forget.  Must be <= 1");

		/// <summary>
		/// How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.
		/// </summary>
		SRSettingI learningRateForgetLogOffset = SRSettingI(8, 1, "learningRateForgetLogOffset",
			"Learning Rate Forget Log Offset",
			"LrnRtFrgtLogOffst",
			"How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// 0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago. Must NOT exceed NEURON_HISTORY - 1.
		/// </summary>
		SRSettingI learningRateTicksOffset = SRSettingI(2, 2, "learningRateTicksOffset",
			"Learning Rate Ticks Offset",
			"LrnRtTcksOffst",
			"0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago. Must NOT exceed NEURON_HISTORY - 1.");

		/// <summary>
		/// How fast confidence decays over time.
		/// </summary>
		SRSettingF confidenceForgetFactor = SRSettingF(0.999999f, 2, "confidenceForgetFactor",
			"Confidence Forget Factor",
			"ConfFrgtFctr",
			"How fast confidence decays over time.");

		/// <summary>
		/// How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.
		/// </summary>
		SRSettingI confidenceForgetLogOffset = SRSettingI(8, 2, "confidenceForgetLogOffset",
			"Confidence Forget Log Offset",
			"ConfFrgtLogOffst",
			"How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.");

		/// <summary>
		/// How rapidly confidence increases on a correct stimulus match.
		/// </summary>
		SRSettingF confidenceAdjustmentUpRate = SRSettingF(1.01f, 2, "confidenceAdjustmentUpRate",
			"Confidence Adjustment Up Rate",
			"ConfAdjUpRt",
			"How rapidly confidence increases on a correct stimulus match.");

		/// <summary>
		/// If a link match is not correct this is how much confidence decays.
		/// </summary>
		SRSettingF confidenceAdjustmentDownRate = SRSettingF(getDecayMultiplier(200.0f), 2, "confidenceAdjustmentDownRate",
			"Confidence Adjustment Down Rate",
			"ConfAdjDnRt",
			"If a link match is not correct this is how much confidence decays.");

		/// <summary>
		/// Confidence can not fall below this level.
		/// </summary>
		SRSettingF minimumConfidence = SRSettingF(0.0001f, 2, "minimumConfidence",
			"Minimum Confidence",
			"MinConf",
			"Confidence can not fall below this level.");

		/// <summary>
		/// Confidence can not exceed this level.
		/// </summary>
		SRSettingF maximumConfidence = SRSettingF(0.9999f, 2, "maximumConfidence",
			"Maximum Confidence",
			"MaxConf",
			"Confidence can not exceed this level.");

		/// <summary>
		/// Initial confidence after a reroute.
		/// </summary>
		SRSettingF rerouteConfidenceSet = SRSettingF(0.5f, 2, "rerouteConfidenceSet",
			"Reroute Confidence Set",
			"RertConfSet",
			"Initial confidence after a reroute.");

		// Map of default settings, key is Tag, value is SRSetting
		std::map<std::string, SRSSetting*> settings;

		// Clears the settings map then
		// clones the settingsDefaults into the settings map.
		void SetValuesToDefaults() {
			for (auto& [tag, setting] : settings) {
				setting->Value = setting->DefaultValue;
			}
		}

		void SetValuesToOriginals() {
			for (auto& [tag, setting] : settings) {
				setting->Value = setting->OriginalValue;
			}
		}

		void SetValuesToPrevious() {
			for (auto& [tag, setting] : settings) {
				setting->Value = setting->PreviousValue;
			}
		}

		void SetOriginalsToValues() {
			for (auto& [tag, setting] : settings) {
				setting->OriginalValue = setting->Value;
			}
		}

		void SetOriginalsToDefaults() {
			for (auto& [tag, setting] : settings) {
				setting->OriginalValue = setting->DefaultValue;
			}
		}

		void SetOriginalsToPrevious() {
			for (auto& [tag, setting] : settings) {
				setting->OriginalValue = setting->PreviousValue;
			}
		}

		void SetPreviousToValues() {
			for (auto& [tag, setting] : settings) {
				setting->PreviousValue = setting->Value;
			}
		}

		void SetPreviousToOriginals() {
			for (auto& [tag, setting] : settings) {
				setting->PreviousValue = setting->OriginalValue;
			}
		}

		void SetPreviousToDefaults() {
			for (auto& [tag, setting] : settings) {
				setting->PreviousValue = setting->DefaultValue;
			}
		}

		bool WriteSettingsToJson(const std::string& filename) const {
			nlohmann::json j;
			for (const auto& [tag, setting] : settings) {
				nlohmann::json s;
				s["Tag"] = setting->Tag;
				s["UILabel"] = setting->UILabel;
				s["Name"] = setting->Name;
				s["Description"] = setting->Description;
				s["SettingRow"] = setting->SettingRow;
				switch (setting->Type) {
				case SettingType::F:
					s["Type"] = "F";
					s["Value"] = setting->F();
					s["DefaultValue"] = setting->DefaultValue.f;
					s["OriginalValue"] = setting->OriginalValue.f;
					s["PreviousValue"] = setting->PreviousValue.f;
					break;
				case SettingType::D:
					s["Type"] = "D";
					s["Value"] = setting->D();
					s["DefaultValue"] = setting->DefaultValue.d;
					s["OriginalValue"] = setting->OriginalValue.d;
					s["PreviousValue"] = setting->PreviousValue.d;
					break;
				case SettingType::I:
					s["Type"] = "I";
					s["Value"] = setting->I();
					s["DefaultValue"] = setting->DefaultValue.i;
					s["OriginalValue"] = setting->OriginalValue.i;
					s["PreviousValue"] = setting->PreviousValue.i;
					break;
				}
				j.push_back(s);
			}
			std::ofstream ofs(filename);
			ofs << j.dump(4);
			return true;
		}

		bool ReadSettingsFromJson(const std::string& filename) {
			std::ifstream ifs(filename);
			nlohmann::json j;
			ifs >> j;
			for (const auto& s : j) {
				std::string tag = s["Tag"];
				if (settings.find(tag) != settings.end()) {
					SRSSetting* setting = settings[tag];
					setting->Description = s["Description"].get<std::string>();
					setting->UILabel = s["UILabel"].get<std::string>();
					setting->SettingRow = s["SettingRow"].get<int>();
					switch (setting->Type) {
					case SettingType::F:
						setting->Value.f = s["Value"].get<float>();
						setting->OriginalValue.f = s["OriginalValue"].get<float>();
						setting->PreviousValue.f = s["PreviousValue"].get<float>();
						// Do not set default value.
						break;
					case SettingType::D:
						setting->Value.d = s["Value"].get<double>();
						setting->OriginalValue.d = s["OriginalValue"].get<double>();
						setting->PreviousValue.d = s["PreviousValue"].get<double>();
						break;
					case SettingType::I:
						setting->Value.i = s["Value"].get<int>();
						setting->OriginalValue.i = s["OriginalValue"].get<int>();
						setting->PreviousValue.i = s["PreviousValue"].get<int>();
						break;
					}
				}
			}
			return true;
		}

		CortexSettings() {
			// Setup the settings map
			settings.emplace("chargeDepletionRate", &chargeDepletionRate);
			settings.emplace("confidenceAdjustmentDownRate", &confidenceAdjustmentDownRate);
			settings.emplace("confidenceAdjustmentUpRate", &confidenceAdjustmentUpRate);
			settings.emplace("confidenceForgetFactor", &confidenceForgetFactor);
			settings.emplace("confidenceForgetLogOffset", &confidenceForgetLogOffset);
			settings.emplace("connectionThrottle", &connectionThrottle);
			settings.emplace("energyDepletionOnFire", &energyDepletionOnFire);
			settings.emplace("energyRechargeRate", &energyRechargeRate);
			settings.emplace("growthRate", &growthRate);
			settings.emplace("highEnergyThreshold", &highEnergyThreshold);
			settings.emplace("learningRateAgeFactor", &learningRateAgeFactor);
			settings.emplace("learningRateForgetFactor", &learningRateForgetFactor);
			settings.emplace("learningRateForgetLogOffset", &learningRateForgetLogOffset);
			settings.emplace("learningRateGoodnessFactor", &learningRateGoodnessFactor);
			settings.emplace("learningRateTicksOffset", &learningRateTicksOffset);
			settings.emplace("linkActivityDecayRate", &linkActivityDecayRate);
			settings.emplace("linkActivityLearningFactor", &linkActivityLearningFactor);
			settings.emplace("linkStimulusToActivityFactor", &linkStimulusToActivityFactor);
			settings.emplace("lowEnergyThreshold", &lowEnergyThreshold);
			settings.emplace("maxEnergy", &maxEnergy);
			settings.emplace("maximumConfidence", &maximumConfidence);
			settings.emplace("minimumConfidence", &minimumConfidence);
			settings.emplace("overallLearnRate", &overallLearnRate);
			settings.emplace("rerouteConfidenceSet", &rerouteConfidenceSet);
			settings.emplace("rerouteProbability", &rerouteProbability);
			settings.emplace("rerouteThreshold", &rerouteThreshold);
		}
	};
}
