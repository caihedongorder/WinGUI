#include "CheckBox.h"
#include <windowsx.h>

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(CheckBox, ButtonBase)
	IMPLEMENT_OBJECT_END()

	CheckBox::CheckBox(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow, HWND InParentHandle)
		:ButtonBase(InPosX,InPosY,InSizeX,InSizeY, BS_AUTOCHECKBOX,InTopWindow,InParentHandle)
	{
		mIsCheck = IsCheck();

		GetOnClick().AddClassMethod(this, &CheckBox::OnClick);
	}

	void CheckBox::SetCheck(bool bCheck, bool bFireEvent)
	{
		Button_SetCheck(hwnd, bCheck);

		if (bFireEvent)
		{
			OnClick();
		}
	}

	void CheckBox::AutoCheck(bool bAutoCheck)
	{
		mCtrlStyle &= ~BS_TYPEMASK;

		if (bAutoCheck)
		{
			mCtrlStyle |= BS_AUTOCHECKBOX;
		}
		else
		{
			mCtrlStyle |= BS_CHECKBOX;
		}
		Button_SetStyle(hwnd, mCtrlStyle, TRUE);
	}

	bool CheckBox::IsCheck() const
	{
		return Button_GetCheck(hwnd) ? true : false;
	}

	void CheckBox::OnClick()
	{
		auto bCheck = IsCheck();
		if (bCheck != mIsCheck)
		{
			mIsCheck = bCheck;

			mOnCheckBoxSelChanged.Broadcast(mIsCheck);
		}
	}

}