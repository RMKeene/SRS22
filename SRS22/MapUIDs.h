#pragma once

/// <summary>
/// Never delete or reorder these, only add new map names.
/// </summary>
enum class MapUidE {
	RANDOM_MAP = 0,

	CAMERAATTNSPOT_MAP,
	CAMERADIFFERENCE_MAP,
	CAMERAFOVEA_MAP,
	CAMERAMOTIONXY_MAP,
	DRAWIN_MAP,
	DRAWOUT_MAP,
	HEARING_MAP,
	SCREENATTNSPOT_MAP,
	SCREENDIFFERENCE_MAP,
	SCREENFOVEA_MAP,
	SCREENMOTION_MAP,
	TEXTCCURRENTCHAR_MAP,
	TEXTOUT_MAP,
	PHONEME_MAP,

	// Always last.
	MapUidECount
};