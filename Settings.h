#pragma once

namespace SRS22 {

	class Settings
	{
	public:
		static Settings globalSettings;
		std::string iniFileName = "SRS22.ini";
		mINI::INIStructure ini;

		bool Load();
		bool Save();
		void Reset();

		void SettingsToIni();
		void IniToSettings();

		bool has(std::string section, std::string key);

		int GetInt(std::string section, std::string key, int d);
		std::string GetString(std::string section, std::string key, std::string d);
		float GetFloat(std::string section, std::string key, float d);
		POINT GetPoint(std::string section, std::string key, POINT d);
		RECT GetRect(std::string section, std::string key, RECT d);
		SIZE GetSize(std::string section, std::string key, SIZE d);
		wxRect GetWxRect(std::string section, std::string key, wxRect d);

		void SetInt(std::string section, std::string key, int v);
		void SetString(std::string section, std::string key, std::string v);
		void SetFloat(std::string section, std::string key, float v);
		void SetPoint(std::string section, std::string key, POINT v);
		void SetRect(std::string section, std::string key, RECT v);
		void SetSize(std::string section, std::string key, SIZE v);
		void SetWxRect(std::string section, std::string key, wxRect v);

		wxRect monitorFrameRect;
		wxRect topTextFrameRect;
		wxRect topVideoFrameRect;
		wxRect whiteboardFrameRect;
	};

}
