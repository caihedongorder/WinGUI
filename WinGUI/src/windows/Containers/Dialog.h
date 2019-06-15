#pragma once
#include <windows/Containers/TopWindow.h>

namespace WinGUI
{
	class WIN_GUI_API Dialog : public TopWindow
	{
		DECLARE_OBJECT(WIN_GUI_API, Dialog, TopWindow)
	public:
		using TopWindow::TopWindow;

	protected:
		virtual bool OnCreate() override;
	};
}
