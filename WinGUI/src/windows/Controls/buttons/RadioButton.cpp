#include "RadioButton.h"
#include <windowsx.h>
#include <windows/Containers/WinContainterBase.h>
#include <string>
#include <windows/Containers/TopWindow.h>

namespace WinGUI
{

	RadioButton::RadioButton(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, u32 InCtrlStyle, class TopWindow* InTopWindow, HWND InParentHandle)
		:ButtonBase(InPosX, InPosY, InSizeX, InSizeY, BS_AUTORADIOBUTTON | InCtrlStyle, InTopWindow, InParentHandle)
	{
	}

	void RadioButton::SetCheck(bool bCheck, bool bFireEvent)
	{
		Button_SetCheck(hwnd, bCheck);

		if (bFireEvent)
		{
			GetOnClick().Broadcast();
		}
	}
	void RadioButton::AutoCheck(bool bAutoCheck)
	{
		mCtrlStyle &= ~BS_TYPEMASK;

		if (bAutoCheck)
		{
			mCtrlStyle |= BS_AUTORADIOBUTTON;
		}
		else
		{
			mCtrlStyle |= BS_RADIOBUTTON;
		}
		Button_SetStyle(hwnd, mCtrlStyle, TRUE);
	}

	bool RadioButton::IsCheck() const
	{
		return Button_GetCheck(hwnd) ? true : false;
	}

	RadioButtonGroup::RadioButtonGroup(class WinContainerBase* InParent)
		:mParent(InParent)
	{

	}

	RadioButtonGroup::~RadioButtonGroup()
	{

	}

	RadioButtonGroup& RadioButtonGroup::AddRadioButton(const std::wstring& InText, u32 x, u32 y, u32 w, u32 h, class TopWindow* InTopWindow, HWND InHandle)
	{
		auto radioButton = mParent->CreateSubWindow<RadioButton>(InTopWindow->GetUniqueCtrlName("radio_button"), x, y, w, h, mbFirstCreateRadioButton ? WS_GROUP : 0, InTopWindow, InHandle);
		radioButton->SetText(InText);
		if (mbFirstCreateRadioButton)
		{
			radioButton->SetCheck(true, false);
			mSelIndex = 0;
		}
		
		u32 iRadioButtonIndex = mNextRadioIndex++;
		radioButton->GetOnClick().AddLambda([this,iRadioButtonIndex]() {
			OnSelRadioButton(iRadioButtonIndex);
		});
		
		mbFirstCreateRadioButton = false;
		return *this;
	}

	void RadioButtonGroup::OnSelRadioButton(u32 InRBIndex)
	{
		mOnRadioButtonSelChanged.Broadcast(InRBIndex);
		mSelIndex = InRBIndex;
	}

}