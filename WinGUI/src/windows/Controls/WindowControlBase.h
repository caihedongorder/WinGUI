#pragma once
#include <windows/WindowBase.h>


namespace WinGUI
{
	class WIN_GUI_API WinCtrlBase : public WinBase
	{
		DECLARE_OBJECT(WIN_GUI_API, WinCtrlBase, WinBase)
	public:
		typedef WinBase SuperClass;
	public:
		WinCtrlBase(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);

		void SetText(const std::wstring& InText);
	protected:
		HWND createControl(const std::wstring& InCtrlClassName, const std::wstring& InCtrlTextName, HWND InParentHandle,const u32 InCtrlStyle);
	protected:
		u32 mCtrlStyle = 0;
		u32 mCtrlId = 0;
	};
}
