#pragma once
#include <Core.h>

#if defined(WIN_GUI_DLL) // inside DLL
#   define WIN_GUI_API   __declspec(dllexport)
#else // outside DLL
#   define WIN_GUI_API   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

#define Super __super
