#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

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

			int SettingRow = 0;
			std::string Tag;
			std::string Name;
			std::string Description;
			/// <summary>
			/// Used by the UI to hook in the UI element to the setting.
			/// </summary>
			void* clientData = nullptr;

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

		// Map of settings, key is Tag, value is SRSetting
		std::map<std::string, SRSetting> settings = {
		};

		// What SetToDefaults() will set the settings to.
		std::map<std::string, SRSetting> settingsDefaults = {
			{"chargeDepletionRate", SRSettingF(getDecayMultiplier(5.0f), 1, "chargeDepletionRate",
				"Charge Depletion Rate", "How much a neuron's Charge decays toward 0.0f each tick.")},
			{"growthRate", SRSettingF(0.01f, 1, "growthRate",
				"Growth Rate", "How much the cortex usable neurons expands per tick.")},
			{"energyRechargeRate", SRSettingF(0.02f, 1, "energyRechargeRate",
				"Energy Recharge Rate", "How much energy a neuron gains each tick.")},
			{"lowEnergyThreshold", SRSettingF(0.1f, 1, "lowEnergyThreshold",
				"Low Energy Threshold", "If energy falls below this the neuron is changed to disabled. It is too tired.")},
			{"highEnergyThreshold", SRSettingF(0.9f, 1, "highEnergyThreshold",
				"High Energy Threshold", "If energy is above this then the neuron is changed to enabled.")},
			{"energyDepletionOnFire", SRSettingF(0.9f * NEURON_UPSTREAM_LINKS_INVERSE, 1, "energyDepletionOnFire",
				"Energy Depletion On Fire", "How much energy is subtracted if the neuron fires. For every Link this gets multiplied by the calculated stimulus.")},
			{"maxEnergy", SRSettingF(2.0f, 2, "maxEnergy",
				"Max Energy", "The highest reserve energy a neuron may have. This is the maximum value for energyCeiling.")},
			{"connectionThrottle", SRSettingF(0.5f, 2, "connectionThrottle",
				"Connection Throttle", "How strongly links stimulus effect the neuron (gets multiplied by NEURON_UPSTREAM_LINKS_INVERSE.)")},
			{"rerouteThreshold", SRSettingF(0.001f, 2, "rerouteThreshold",
				"Reroute Threshold", "If confidence falls below this then a reroute might happen.")},
			{"rerouteProbability", SRSettingF(0.01f, 2, "rerouteProbability",
				"Reroute Probability", "Probability of a reroute on any given tick if confidence is below rerouteThreshold.")},
			{"overallLearnRate", SRSettingF(0.05f, 2, "overallLearnRate",
				"Overall Learning Rate", "General factor of learning rates speed.")},
			{"linkActivityDecayRate", SRSettingF(getDecayMultiplier(2.0f), 2, "linkActivityDecayRate",
				"Link Activity Decay Rate", "How much of the link activity is decayed each tick.")},
			{"linkActivityLearningFactor", SRSettingF(1.1f, 2, "linkActivityLearningFactor",
				"Link Activity Learning Factor", "How much of the link activity is added to the link activity.")},
			{"linkStimulusToActivityFactor", SRSettingF(0.1f, 2, "linkStimulusToActivityFactor",
				"Link Stimulus to Activity Factor", "How much of input stimulus absolute value is added to L.activity.")},
			{"learningRateGoodnessFactor", SRSettingF(0.1f, 2, "learningRateGoodnessFactor",
				"Learning Rate Goodness Factor", "How influential the goodness factor of the brain is on learning rate.")},
			{"learningRateAgeFactor", SRSettingF(1.0f, 2, "learningRateAgeFactor",
				"Learning Rate Age Factor", "Learning rate goes down by the base 2 log of age of the link multiplied by this factor.")},
			{"learningRateForgetFactor", SRSettingF(0.999999f, 3, "learningRateForgetFactor",
				"Learning Rate Forget Factor", "General how fast we forget.  Must be <= 1")},
			{"learningRateForgetLogOffset", SRSettingI(8, 3, "learningRateForgetLogOffset",
				"Learning Rate Forget Log Offset", "How much pre-age neuron links get when new relative to actual age. This is a power of two exponent.")},
			{"learningRateTicksOffset", SRSettingI(2, 3, "learningRateTicksOffset",
				"Learning Rate Ticks Offset", "0 is current charge of self. 1 is charge of self 1 tick ago. 2 is charge of self 2 ticks ago. Must NOT exceed NEURON_HISTORY - 1.")},
			{"confidenceForgetFactor", SRSettingF(0.999999f, 3, "confidenceForgetFactor",
				"Confidence Forget Factor", "How fast confidence decays over time.")},
			{"confidenceForgetLogOffset", SRSettingI(8, 3, "confidenceForgetLogOffset",
				"Confidence Forget Log Offset", "How much pre-age neuron link confidence gets when new relative to actual age. This is a power of two exponent.")},
			{"confidenceAdjustmentUpRate", SRSettingF(1.01f, 3, "confidenceAdjustmentUpRate",
				"Confidence Adjustment Up Rate", "How rapidly confidence increases on a correct stimulus match.")},
			{"confidenceAdjustmentDownRate", SRSettingF(getDecayMultiplier(200.0f), 3, "confidenceAdjustmentDownRate",
				"Confidence Adjustment Down Rate", "If a link match is not correct this is how much confidence decays.")},
			{"minimumConfidence", SRSettingF(0.0001f, 3, "minimumConfidence",
				"Minimum Confidence", "Confidence can not fall below this level.")},
			{"maximumConfidence", SRSettingF(0.9999f, 3, "maximumConfidence",
				"Maximum Confidence", "Confidence can not exceed this level.")},
			{"rerouteConfidenceSet", SRSettingF(0.5f, 3, "rerouteConfidenceSet",
				"Reroute Confidence Set", "Initial confidence after a reroute.")}
		};

		// Clears the settings map then
		// clones the settingsDefaults into the settings map.
		void ResetSettings() {
			settings.clear();
			for (const auto& [tag, setting] : settingsDefaults) {
				// Deep Clone the setting
				switch (setting.Type) {
				case SettingType::F:
					settings[tag] = SRSettingF(setting.F(), setting.SettingRow, tag, setting.Name, setting.Description);
					break;
				case SettingType::D:
					settings[tag] = SRSettingD(setting.D(), setting.SettingRow, tag, setting.Name, setting.Description);
					break;
				case SettingType::I:
					settings[tag] = SRSettingI(setting.I(), setting.SettingRow, tag, setting.Name, setting.Description);
					break;
				default:
					throw std::runtime_error("Unknown setting type");
			}
		}

		// Optionally, you can provide helper functions to access settings by tag
		SRSetting* GetSetting(const std::string& tag) {
			auto it = settings.find(tag);
			if (it != settings.end()) {
				return &(it->second);
			}
			return nullptr;
		}

		bool RemoveSetting(const std::string& tag) {
			return settings.erase(tag) > 0;
		}

		void AddSetting(const std::string& tag, const SRSetting& setting) {
			settings[tag] = setting;
		}

		void WriteSettingsToJson(const std::string& filename) const {
			nlohmann::json j;
			for (const auto& [tag, setting] : settings) {
				nlohmann::json s;
				s["Tag"] = setting.Tag;
				s["Name"] = setting.Name;
				s["Description"] = setting.Description;
				s["SettingRow"] = setting.SettingRow;
				switch (setting.Type) {
				case SettingType::F:
					s["Type"] = "F";
					s["Value"] = setting.F();
					break;
				case SettingType::D:
					s["Type"] = "D";
					s["Value"] = setting.D();
					break;
				case SettingType::I:
					s["Type"] = "I";
					s["Value"] = setting.I();
					break;
				}
				j.push_back(s);
			}
			std::ofstream ofs(filename);
			ofs << j.dump(4);
		}


		void LoadSettingsFromJson(const std::string& filename, bool createAll = false) {
			std::ifstream ifs(filename);
			if (!ifs.is_open()) {
				// File not found or could not be opened, do nothing
				return;
			}
			nlohmann::json j;
			try {
				ifs >> j;
			}
			catch (...) {
				// Malformed JSON, do nothing
				return;
			}
			for (const auto& s : j) {
				if (!s.contains("Tag") || !s.contains("Type") || !s.contains("Value"))
					continue;
				std::string tag = s["Tag"];
				auto it = settings.find(tag);
				SRSetting* settingPtr = nullptr;
				if (it == settings.end()) {
					if (!createAll)
						continue;
					// Create new setting based on type
					std::string type = s["Type"];
					int settingRow = s.contains("SettingRow") ? s["SettingRow"].get<int>() : 0;
					std::string name = s.contains("Name") ? s["Name"].get<std::string>() : tag;
					std::string description = s.contains("Description") ? s["Description"].get<std::string>() : "";
					if (type == "F" && s["Value"].is_number_float()) {
						SRSettingF newSetting(static_cast<float>(s["Value"]), settingRow, tag, name, description);
						settings[tag] = newSetting;
						settingPtr = &settings[tag];
					}
					else if (type == "D" && s["Value"].is_number()) {
						SRSettingD newSetting(static_cast<double>(s["Value"]), settingRow, tag, name, description);
						settings[tag] = newSetting;
						settingPtr = &settings[tag];
					}
					else if (type == "I" && s["Value"].is_number_integer()) {
						SRSettingI newSetting(static_cast<int>(s["Value"]), settingRow, tag, name, description);
						settings[tag] = newSetting;
						settingPtr = &settings[tag];
					}
					else {
						continue;
					}
				}
				else {
					settingPtr = &it->second;
				}
				if (!settingPtr)
					continue;
				std::string type = s["Type"];
				if (type == "F" && s["Value"].is_number_float()) {
					settingPtr->Set(static_cast<float>(s["Value"]));
				}
				else if (type == "D" && s["Value"].is_number()) {
					settingPtr->Set(static_cast<double>(s["Value"]));
				}
				else if (type == "I" && s["Value"].is_number_integer()) {
					settingPtr->Set(static_cast<int>(s["Value"]));
				}
				// Optionally update Name, Description, SettingRow if present
				if (s.contains("Name")) settingPtr->Name = s["Name"];
				if (s.contains("Description")) settingPtr->Description = s["Description"];
				if (s.contains("SettingRow")) settingPtr->SettingRow = s["SettingRow"];
			}
		}
	}
};
}// Removes a setting by tag from the settings map. Returns true if removed, false if not found.

