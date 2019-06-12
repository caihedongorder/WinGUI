#pragma once
#include <windows/Controls/buttons/ButtonBase.h>

namespace WinGUI
{
	class WIN_GUI_API CheckBox : public ButtonBase
	{
	public:
		typedef ButtonBase SuperClass;
		enum EWT { ID = EWindowType_CheckBox };
	public:
		CheckBox(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle);

		void SetCheck(bool bCheck,bool bFireEvent = true);

		void AutoCheck(bool bAutoCheck);

		bool IsCheck() const;

		EventOnCheckBoxSelChanged& GetOnCheckBoxSelChanged() { return mOnCheckBoxSelChanged; }
	private:
		void OnClick();
	private:
		bool mIsCheck;

		EventOnCheckBoxSelChanged mOnCheckBoxSelChanged;
	};
}
