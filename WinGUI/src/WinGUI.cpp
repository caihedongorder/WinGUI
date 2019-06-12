#include "WinGui.h"

namespace WinGUI
{
	void ShowMessageBox(const std::wstring& InMsg, u32 msgType, const std::wstring& InTitle, HWND InHandle)
	{
		::MessageBox(InHandle, InMsg.c_str(), InTitle.c_str(), msgType);
	}
}