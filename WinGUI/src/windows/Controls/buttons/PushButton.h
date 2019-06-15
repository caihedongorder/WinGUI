#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API PushButton : public ButtonBase
	{
		DECLARE_OBJECT(WIN_GUI_API, PushButton, ButtonBase)
	public:
		PushButton(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);
	};
}
