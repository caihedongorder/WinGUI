#pragma once
#include <typedefines.h>
#include <apps/Application.h>
#include <windows/Containers/Dialog.h>
#include <windows/Controls/buttons/Button.h>


namespace WinGUI
{
	void WIN_GUI_API ShowMessageBox(const std::wstring& InMsg, u32 msgType = MB_OK, const std::wstring& InTitle = TEXT(""), HWND InHandle = NULL);
}



