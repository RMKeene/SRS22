// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

// There is a whole cascade of errors if the windows headers are not in the correct order!
//#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#ifndef __wtypes_h__
#include <wtypes.h>
#endif
#ifndef __WINDEF_
#include <windef.h>
#endif
#include <gdiplus.h>

#include "wx/setup.h"
// add headers that you want to pre-compile here
#include "wx/wxprec.h"
// for all others, include the necessary headers
#ifndef WX_PRECOMP
#include "wx/app.h"
#include "wx/log.h"
#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/stattext.h"
#include "wx/menu.h"
#include "wx/layout.h"
#include "wx/msgdlg.h"
#include "wx/icon.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/settings.h"
#endif

#undef free
#include <opencv2/opencv.hpp>

#include <nlohmann/json.hpp>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>

#include "ini.h"

#endif //PCH_H
