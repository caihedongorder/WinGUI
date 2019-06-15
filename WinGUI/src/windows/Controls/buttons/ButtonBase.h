#pragma once
#include <windows/Controls/WindowControlBase.h>
#include <windows/Events/Event.h>


namespace WinGUI
{
	class WIN_GUI_API ButtonBase : public WinCtrlBase
	{
		DECLARE_OBJECT(WIN_GUI_API, ButtonBase, WinCtrlBase)
	public:
		ButtonBase(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY,u32 InCtrlStyle,class TopWindow* InTopWindow, HWND InParentHandle);
		EventOnButtonClick& GetOnClick() { return mEventOnClick; }

		void Click() { mEventOnClick.Broadcast(); }
	protected:
		virtual bool OnCreate() override;

	private:
		EventOnButtonClick mEventOnClick;
	};

}