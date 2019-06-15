#pragma once
#include <Core_Defines.h>

#if defined(CORE_DLL) // inside DLL
#   define CORE_API   __declspec(dllexport)
#else // outside DLL
#   define CORE_API   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

namespace Core
{
	void CORE_API Init();
	void CORE_API UnIint();
}

