#include "Settings.h"
#include <boost/algorithm/string.hpp>

Settings Settings::globalSettings;

bool Settings::Load() {
	mINI::INIFile file(iniFileName);
	bool r = file.read(ini);
	if (!r)
		throw std::runtime_error("No SRS22.ini file, or unreadable.");
	return true;
}

bool Settings::Save() {
	mINI::INIFile file(iniFileName);
	file.write(ini);
	return true;
}

void Settings::Reset() {
	ini.clear();
	IniToSettings();
	SettingsToIni();
}

void Settings::SettingsToIni() {
	SetWxRect("WindowLayout", "monitorFrameRect", monitorFrameRect);
	SetWxRect("WindowLayout", "topTextFrameRect", topTextFrameRect);
	SetWxRect("WindowLayout", "topVideoFrameRect", topVideoFrameRect);
	SetWxRect("WindowLayout", "whiteboardFrameRect", whiteboardFrameRect);
}

void Settings::IniToSettings() {
	// This is where default values are defined.
	monitorFrameRect = GetWxRect("WindowLayout", "monitorFrameRect", wxRect(10, 10, 2400, 1000));
	topTextFrameRect = GetWxRect("WindowLayout", "topTextFrameRect", wxRect(90, 90, 500, 650));
	topVideoFrameRect = GetWxRect("WindowLayout", "topVideoFrameRect", wxRect(180, 180, 512, 512));
	whiteboardFrameRect = GetWxRect("WindowLayout", "whiteboardFrameRect", wxRect(270, 270, 800, 500));
}

bool Settings::has(std::string section, std::string key) {
	return ini.has(section) && ini[section].has(key);
}

int Settings::GetInt(std::string section, std::string key, int d) {
	if (has(section, key))
		return std::stoi(ini[section][key]);
	return d;
}

std::string Settings::GetString(std::string section, std::string key, std::string d) {
	if (has(section, key))
		return ini[section][key];
	return d;

}

float Settings::GetFloat(std::string section, std::string key, float d) {
	if (has(section, key))
		return std::stof(ini[section][key]);
	return d;

}

POINT Settings::GetPoint(std::string section, std::string key, POINT d) {
	if (has(section, key)) {
		std::string s = ini[section][key];
		std::list<std::string> L;
		boost::split(L, s, boost::is_any_of(","));
		if (L.size() == 2) {
			auto LL = L.begin();
			POINT p;
			p.x = std::stol(*LL); LL++;
			p.y = std::stol(*LL);
			return p;
		}
	}
	return d;
}

RECT Settings::GetRect(std::string section, std::string key, RECT d) {
	if (has(section, key)) {
		std::string s = ini[section][key];
		std::list<std::string> L;
		boost::split(L, s, boost::is_any_of(","));
		if (L.size() == 4) {
			auto LL = L.begin();
			// We store in the same order as the RECT struct definition.
			RECT p;
			p.left = std::stol(*LL); LL++;
			p.top = std::stol(*LL); LL++;
			p.right = std::stol(*LL); LL++;
			p.bottom = std::stol(*LL); LL++;
			return p;
		}
	}
	return d;
}

SIZE Settings::GetSize(std::string section, std::string key, SIZE d) {
	if (has(section, key)) {
		std::string s = ini[section][key];
		std::list<std::string> L;
		boost::split(L, s, boost::is_any_of(","));
		if (L.size() == 2) {
			auto LL = L.begin();
			SIZE p;
			p.cx = std::stol(*LL); LL++;
			p.cy = std::stol(*LL);
			return p;
		}
	}
	return d;
}

wxRect Settings::GetWxRect(std::string section, std::string key, wxRect d) {
	if (has(section, key)) {
		std::string s = ini[section][key];
		std::list<std::string> L;
		boost::split(L, s, boost::is_any_of(","));
		if (L.size() == 4) {
			auto LL = L.begin();
			// We store in the same order as the RECT struct definition.
			wxRect p;
			p.x = std::stol(*LL); LL++;
			p.y = std::stol(*LL); LL++;
			p.width = std::stol(*LL); LL++;
			p.height = std::stol(*LL); LL++;
			return p;
		}
	}
	return d;
}

void Settings::SetInt(std::string section, std::string key, int v) {
	ini[section][key] = std::to_string(v);
}

void Settings::SetString(std::string section, std::string key, std::string v) {
	ini[section][key] = v;
}

void Settings::SetFloat(std::string section, std::string key, float v) {
	ini[section][key] = std::to_string(v);
}

void Settings::SetPoint(std::string section, std::string key, POINT v) {
	ini[section][key] = std::to_string(v.x) + "," + std::to_string(v.y);
}

void Settings::SetRect(std::string section, std::string key, RECT v) {
	ini[section][key] = std::to_string(v.left) + "," + std::to_string(v.top) +
		"," + std::to_string(v.right) + "," + std::to_string(v.bottom);
}

void Settings::SetSize(std::string section, std::string key, SIZE v) {
	ini[section][key] = std::to_string(v.cx) + "," + std::to_string(v.cy);
}

void Settings::SetWxRect(std::string section, std::string key, wxRect v) {
	ini[section][key] = std::to_string(v.x) + "," + std::to_string(v.y) +
		"," + std::to_string(v.width) + "," + std::to_string(v.height);
}


