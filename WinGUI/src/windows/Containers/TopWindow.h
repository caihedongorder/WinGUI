#pragma once
#include <windows/Containers/WinContainterBase.h>
#include <functional>
#include "windows/Events/Event.h"

namespace WinGUI
{
	class WIN_GUI_API TopWindow : public WinContainerBase
	{
	public:
		typedef WinContainerBase SuperClass;
		enum EWT { ID = EWindowType_TopWindow };
	public:
		using WinContainerBase::WinContainerBase;

		virtual bool OnClose();

		void SetText(const std::wstring& InText);

		EventOnWindowClose& GetEventOnCloseWindow() { return mEventOnClose; }

		u32 NextCtrlId() { return mNextCtrlId++; }
	private:
		EventOnWindowClose mEventOnClose;
		u32 mNextCtrlId = 0;
	};
}
