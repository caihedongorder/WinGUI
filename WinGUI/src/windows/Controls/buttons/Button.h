#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API Button : public ButtonBase
	{
	public:
		typedef ButtonBase SuperClass;
		enum EWT { ID = EWindowType_Button	};

	public:
		Button(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);

		//virtual u32 GetWindowType() const override { return ID; }
		//virtual bool CanCast(u32 InWindowType) const override { return InWindowType == ID || InWindowType == SuperClass::ID; }

	
	};
}
