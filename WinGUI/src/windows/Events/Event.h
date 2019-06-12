#pragma once
#include <Delegate.h>

namespace WinGUI
{
	typedef Core::TDelegate<void> EventOnButtonClick;
	typedef Core::TDelegate<void, bool> EventOnCheckBoxSelChanged;
	typedef Core::TDelegate<void, i32> EventOnRadioButtonSelChanged;

	typedef Core::TDelegate<void, i32> EventOnComboBoxSelChanged;


	typedef Core::TDelegate<void> EventOnWindowClose;
}