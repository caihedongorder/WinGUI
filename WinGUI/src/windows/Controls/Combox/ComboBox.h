#pragma once
#include <windows/Controls/WindowControlBase.h>
#include <windows/events/Event.h>

namespace WinGUI
{
	class WIN_GUI_API ComboBox : public WinCtrlBase
	{
		DECLARE_OBJECT(WIN_GUI_API, ComboBox, WinCtrlBase)
	public:
		ComboBox(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);

		ComboBox& AddItem(const std::wstring& InText);
		ComboBox& InsertItem(i32 InPos, const std::wstring& InText);
		ComboBox& SetText(const std::wstring& InText);
		ComboBox& SetLimit(i32 InLimit);
		ComboBox& DeleteItem(i32 InItemIdx);
		ComboBox& SetItemHeight(i32 InItemHeight);
		ComboBox& SetExtendedUI(u32 InFlags);
		ComboBox& SelectItem(i32 InItemIdx, bool bFireEvent);

		std::wstring GetText() const;
		std::wstring GetItemText(i32 InItemIdx) const;
		u32 GetItemCount() const;
		i32 GetSelItemIndex() const;
		i32 FindItem(const std::wstring& InItemText,i32 InStartPos = 0);
		void SetEditCtrlSel(i32 InStartPos, i32 InEndPos);
		// 获取编辑框文本选中字符串索引 [start,end)
		void GetEditCtrlSel(i32& OutStartPos, i32& OutEdnPos);
		void ClearAllItems();

		u32 GetExtendedUI() const;
		i32 GetItemHeight() const;

		void ShowDropdown();
		void HideDropdown();
		
		EventOnComboBoxSelChanged& GetOnComboBoxSelChanged() { return mOnComboxSelChange; }
		
		void FireEventOnSelChange();
	private:
		EventOnComboBoxSelChanged mOnComboxSelChange;

		i32 mSelItemIndex = INDEX_NONE;
	};
}
