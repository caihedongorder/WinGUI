#include <apps/Application.h>
#include "Windows/Containers/TopWindow.h"
#include "Windows/Controls/buttons/Button.h"
#include <algorithm>

namespace WinGUI
{
	void ApplicationBase::Event_Button_OnClick(HWND InHandle, u32 InCtrlId)
	{
		if (auto pButton = FindSubWindow<ButtonBase>(InHandle,InCtrlId))
		{
			pButton->Click();
		}
	}
}