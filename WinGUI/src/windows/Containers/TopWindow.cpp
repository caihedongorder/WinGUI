#include "TopWindow.h"

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(TopWindow, WinContainerBase)
	IMPLEMENT_OBJECT_END()

	bool TopWindow::OnClose()
	{
		return true;
	}

	void TopWindow::SetText(const std::wstring& InText)
	{
		::SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)InText.c_str());
	}

}