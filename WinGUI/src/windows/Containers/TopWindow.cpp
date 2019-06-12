#include "TopWindow.h"

namespace WinGUI
{

	bool TopWindow::OnClose()
	{
		return true;
	}

	void TopWindow::SetText(const std::wstring& InText)
	{
		::SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)InText.c_str());
	}

}