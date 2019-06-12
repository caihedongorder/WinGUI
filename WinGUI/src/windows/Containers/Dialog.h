#pragma once
#include <windows/Containers/TopWindow.h>

namespace WinGUI
{
	class WIN_GUI_API Dialog : public TopWindow
	{
	public:
		typedef TopWindow SuperClass;
		enum EWT { ID = EWindowType_Dialog };
	public:
		using TopWindow::TopWindow;

	protected:
		virtual bool OnCreate() override;
	};
}
