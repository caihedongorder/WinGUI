#include <apps/Application.h>
#include <Windows/Containers/TopWindow.h>
#include <Windows/Controls/Combox/ComboBox.h>
#include <algorithm>

namespace WinGUI
{
	void ApplicationBase::Event_ComboBox_SelChange(HWND InHandle, u32 InCtrlId)
	{
		if (auto pComboBox = FindSubWindow<ComboBox>(InHandle, InCtrlId))
		{
			pComboBox->FireEventOnSelChange();
		}
	}
}