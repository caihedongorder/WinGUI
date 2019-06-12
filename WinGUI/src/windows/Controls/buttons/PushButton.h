#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API PushButton : public ButtonBase
	{
	public:
		typedef ButtonBase SuperClass;
		enum EWT { ID = EWindowType_CheckBox };
	public:
		PushButton(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);
	};
}
