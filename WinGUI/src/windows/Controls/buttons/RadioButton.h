#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API RadioButton : public ButtonBase
	{
	public:
		typedef ButtonBase SuperClass;
		enum EWT { ID = EWindowType_RadioButton };
	public:
		RadioButton(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, u32 InCtrlStyle, class TopWindow* InTopWindow, HWND InParentHandle);

		void SetCheck(bool bCheck, bool bFireEvent = true);

		bool IsCheck() const;

		void AutoCheck(bool bAutoCheck);
	};

	class WIN_GUI_API RadioButtonGroup
	{
	public:
		RadioButtonGroup(class WinContainerBase* InParent);
		~RadioButtonGroup();

		RadioButtonGroup& AddRadioButton(const std::wstring& InText, u32 x, u32 y, u32 w, u32 h, class TopWindow* InTopWindow,HWND InHandle);
		
		EventOnRadioButtonSelChanged& GetOnRadioButtonSelChanged() { return mOnRadioButtonSelChanged; }
		
		i32 GetSelIndex() const { return mSelIndex; }
	protected:
		void OnSelRadioButton(u32 InRBIndex);
	private:
		EventOnRadioButtonSelChanged mOnRadioButtonSelChanged;
		class WinContainerBase* mParent;
		bool mbFirstCreateRadioButton = true;
		u32 mNextRadioIndex = 0;
		i32 mSelIndex = INDEX_NONE;
	};
}
