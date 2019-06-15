#include "Button.h"

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(Button, ButtonBase)
	IMPLEMENT_OBJECT_END()

	Button::Button(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY,class TopWindow* InTopWindow, HWND InParentHandle)
		:ButtonBase(InPosX,InPosY,InSizeX,InSizeY,0,InTopWindow,InParentHandle)
	{

	}

}