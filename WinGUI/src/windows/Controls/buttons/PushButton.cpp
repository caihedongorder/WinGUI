#include "PushButton.h"

namespace WinGUI
{

	PushButton::PushButton(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY,class TopWindow* InTopWindow, HWND InParentHandle)
		:ButtonBase(InPosX, InPosY, InSizeX, InSizeY, BS_DEFPUSHBUTTON, InTopWindow, InParentHandle)
	{

	}

}