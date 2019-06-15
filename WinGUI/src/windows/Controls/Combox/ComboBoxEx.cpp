#include "ComboBoxEx.h"

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(ComboBoxEx, WinCtrlBase)
	IMPLEMENT_OBJECT_END()

	ComboBoxEx::ComboBoxEx(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle)
		:WinCtrlBase(InPosX, InPosY, InSizeX, InSizeY, InTopWindow, InParentHandle)
	{
		hwnd = createControl(WC_COMBOBOXEX, TEXT("ComboxEx"), InParentHandle, CBS_SORT | CBS_DROPDOWN);
	}
	
	ComboBoxEx& ComboBoxEx::AddItem(const std::wstring& InText)
	{
		COMBOBOXEXITEM comboBoxItem;
		comboBoxItem.mask = CBEIF_TEXT;
		comboBoxItem.iItem = INDEX_NONE;
		comboBoxItem.pszText = const_cast<wchar_t*>(InText.data());
		comboBoxItem.cchTextMax = i32(InText.length()) + 1;
		comboBoxItem.iImage = I_IMAGENONE;
		comboBoxItem.iSelectedImage = I_IMAGENONE;
		comboBoxItem.iOverlay = I_IMAGENONE;
		comboBoxItem.iIndent = 0;
		comboBoxItem.lParam = 0;
		
		::SendMessage(hwnd, CBEM_INSERTITEM, 0, reinterpret_cast<LPARAM>(&comboBoxItem));

		return *this;
	}

}