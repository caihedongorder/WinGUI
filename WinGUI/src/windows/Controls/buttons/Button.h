#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API Button : public ButtonBase
	{
		DECLARE_OBJECT(WIN_GUI_API, Button, ButtonBase)
	public:
		Button(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);
	};
}
