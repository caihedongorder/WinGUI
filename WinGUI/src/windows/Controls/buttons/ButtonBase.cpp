#include "ButtonBase.h"
#include <assert.h>

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(ButtonBase, WinCtrlBase)
	IMPLEMENT_OBJECT_END()

	ButtonBase::ButtonBase(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, u32 InCtrlStyle, class TopWindow* InTopWindow, HWND InParentHandle)
		:WinCtrlBase(InPosX,InPosY,InSizeX,InSizeY, InTopWindow,InParentHandle)
	{
		hwnd  = createControl(WC_BUTTON, TEXT("Button"), InParentHandle, InCtrlStyle);
		assert(hwnd != NULL);
	}

	bool ButtonBase::OnCreate()
	{
		return hwnd != NULL;
	}

}