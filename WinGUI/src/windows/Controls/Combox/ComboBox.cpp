#include "ComboBox.h"
#include <windowsx.h>
#include <vector>

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(ComboBox, WinCtrlBase)
	IMPLEMENT_OBJECT_END()

	ComboBox::ComboBox(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle)
		:WinCtrlBase(InPosX,InPosY,InSizeX,InSizeY, InTopWindow,InParentHandle)
	{
		hwnd = createControl(WC_COMBOBOX, TEXT("Combox"), InParentHandle, CBS_SORT | CBS_DROPDOWN);
	}

	ComboBox& ComboBox::AddItem(const std::wstring& InText)
	{
		ComboBox_AddString(hwnd, InText.c_str());
		return *this;
	}

	ComboBox& ComboBox::InsertItem(i32 InPos, const std::wstring& InText)
	{
		ComboBox_InsertString(hwnd,InPos,InText.c_str());
		return *this;
	}

	ComboBox& ComboBox::SetText(const std::wstring& InText)
	{
		ComboBox_SetText(hwnd,InText.c_str());
		return *this;
	}
	ComboBox& ComboBox::SetLimit(i32 InLimit)
	{
		ComboBox_LimitText(hwnd, InLimit);
		return *this;
	}
	ComboBox& ComboBox::DeleteItem(i32 InItemIdx)
	{
		ComboBox_DeleteString(hwnd,InItemIdx);
		return *this;
	}

	ComboBox& ComboBox::SetItemHeight(i32 InItemHeight)
	{
		ComboBox_SetItemHeight(hwnd, 0, InItemHeight);
		return *this;
	}
	ComboBox& ComboBox::SetExtendedUI(u32 InFlags)
	{
		ComboBox_SetExtendedUI(hwnd, InFlags);
		return *this;
	}

	std::wstring ComboBox::GetText() const
	{
		std::vector<wchar_t> textData;
		auto len = ComboBox_GetTextLength(hwnd);
		textData.resize(len + 1);
		ComboBox_GetText(hwnd, textData.data(), len + 1);

		std::wstring txt;
		txt.assign(textData.cbegin(), textData.cend());
		return txt;
	}

	std::wstring  ComboBox::GetItemText(i32 InItemIdx) const
	{
		std::vector<wchar_t> textData;
		auto len = ComboBox_GetLBTextLen(hwnd,InItemIdx);
		textData.resize(len + 1);
		ComboBox_GetLBText(hwnd,InItemIdx, textData.data());

		std::wstring txt;
		txt.assign(textData.cbegin(), textData.cend());
		return txt;
	}


	u32 ComboBox::GetItemCount() const
	{
		return ComboBox_GetCount(hwnd);
	}
	i32 ComboBox::GetSelItemIndex() const
	{
		return ComboBox_GetCurSel(hwnd);
	}

	i32 ComboBox::FindItem(const std::wstring& InItemText, i32 InStartPos)
	{
		return ComboBox_FindString(hwnd, InStartPos, InItemText.c_str());
	}

	void ComboBox::SetEditCtrlSel(i32 InStartPos, i32 InEndPos)
	{
		ComboBox_SetEditSel(hwnd, InStartPos, InEndPos);
	}

	void ComboBox::GetEditCtrlSel(i32& OutStartPos, i32& OutEdnPos)
	{
		auto SelRange = ComboBox_GetEditSel(hwnd);
		OutStartPos = LOWORD(SelRange);
		OutEdnPos = HIWORD(SelRange);
	}

	void ComboBox::ClearAllItems()
	{
		ComboBox_ResetContent(hwnd);
		mSelItemIndex = INDEX_NONE;
	}

	u32 ComboBox::GetExtendedUI() const
	{
		return ComboBox_GetExtendedUI(hwnd);
	}

	i32 ComboBox::GetItemHeight() const
	{
		return ComboBox_GetItemHeight(hwnd);
	}

	void ComboBox::ShowDropdown()
	{
		ComboBox_ShowDropdown(hwnd, TRUE);
	}

	void ComboBox::HideDropdown()
	{
		ComboBox_ShowDropdown(hwnd, FALSE);
	}

	void ComboBox::FireEventOnSelChange()
	{
		auto newSelItemIdx = GetSelItemIndex();
		if (mSelItemIndex != newSelItemIdx)
		{
			mSelItemIndex = newSelItemIdx;

			mOnComboxSelChange.Broadcast(mSelItemIndex);
		}
	}

	ComboBox& ComboBox::SelectItem(i32 InItemIdx, bool bFireEvent)
	{
		ComboBox_SetCurSel(hwnd, InItemIdx);

		if (bFireEvent)
		{
			FireEventOnSelChange();
		}

		return *this;
	}

}
