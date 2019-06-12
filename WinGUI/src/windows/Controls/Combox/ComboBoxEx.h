#pragma once
#include <windows/Controls/WindowControlBase.h>

namespace WinGUI
{
	class WIN_GUI_API ComboBoxEx : public WinCtrlBase
	{
	public:
		typedef WinCtrlBase SuperClass;
		enum EWT { ID = EWindowType_ComboBoxEx };
	public:
		ComboBoxEx(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);
		ComboBoxEx& AddItem(const std::wstring& InText);

	};
}
