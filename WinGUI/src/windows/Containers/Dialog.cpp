#include "Dialog.h"

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(Dialog, TopWindow)
	IMPLEMENT_OBJECT_END()

#define CLASS_NAME TEXT("MyWndClass")

	bool Dialog::OnCreate()
	{
		hwnd = CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, TEXT("MyWindow"), WS_OVERLAPPEDWINDOW, WinPosX, WinPosY, WinSizeX, WinSizeY, NULL, NULL, NULL, NULL);
		if (hwnd == NULL)
		{
			return false;
		}

		UpdateWindow(hwnd);

		return true;
	}

}