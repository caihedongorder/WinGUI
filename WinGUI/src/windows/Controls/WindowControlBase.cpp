#include "WindowControlBase.h"
#include <Windows/Containers/TopWindow.h>

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(WinCtrlBase, WinBase)
	IMPLEMENT_OBJECT_END()

	WinCtrlBase::WinCtrlBase(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY,class TopWindow* InTopWindow, HWND InParentHandle)
		:WinBase(InPosX,InPosY,InSizeX,InSizeY, InTopWindow,InParentHandle)
		,mCtrlId(InTopWindow->NextCtrlId())
	{

	}

	void WinCtrlBase::SetText(const std::wstring& InText)
	{
		::SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)InText.c_str());
	}

	HWND WinCtrlBase::createControl(const std::wstring& InCtrlClassName, const std::wstring& InCtrlTextName, HWND InParentHandle, const u32 InCtrlStyle)
	{
		mCtrlStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | InCtrlStyle;
		#pragma warning(disable:4312)
		HWND 	hwnd = CreateWindow(
			InCtrlClassName.c_str(), // Predefined class; Unicode assumed
			InCtrlTextName.c_str(),        // Text will be defined later
			mCtrlStyle,  // Styles
			WinPosX,        // x position 
			WinPosY,         // y position 
			WinSizeX,        // Button width
			WinSizeY,        // Button height
			InParentHandle,     // Parent window
			HMENU(mCtrlId),       // No menu
			NULL,
			NULL);      // Pointer not needed
		return hwnd;
	}

}