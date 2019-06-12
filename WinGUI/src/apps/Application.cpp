#include "Application.h"
#include <windows.h>
#include "windows\Containers\TopWindow.h"

namespace WinGUI
{
	extern BOOL RegisterWinClass();
	extern HWND GMainFrameHandle;
	extern ApplicationBase* GApp;


	ApplicationBase::ApplicationBase()
	{
		GApp = this;
	}

	ApplicationBase::~ApplicationBase()
	{
		GApp = nullptr;
	}

	void ApplicationBase::SetMainFrameWindow(HWND InMainFrameHandle)
	{
		GMainFrameHandle = InMainFrameHandle;
	}

	bool ApplicationBase::OnInit()
	{
		if (!RegisterWinClass())
		{
			return false;
		}
		INITCOMMONCONTROLSEX commonCtrlRolsex;
		commonCtrlRolsex.dwSize = sizeof(commonCtrlRolsex);
		commonCtrlRolsex.dwICC = ICC_USEREX_CLASSES;
		InitCommonControlsEx(&commonCtrlRolsex);
		return true;
	}

	void ApplicationBase::OnUnInit()
	{

	}

	void ApplicationBase::OnCloseWindow(HWND InHandle)
	{
		for (auto It = mWindows.begin() ; It!= mWindows.end(); ++It)
		{
			TopWindow* topWin = (TopWindow*)(*It).get();
			if (topWin->GetHandle() == InHandle)
			{
				if (topWin->OnClose())
				{
					if (GMainFrameHandle == InHandle)
					{
						::PostQuitMessage(-1);
					}
					mWindows.erase(It);
				}
				break;
			}
		}
	}

	void ApplicationBase::Run()
	{
		MSG msg;

		while (true)
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				::Sleep(1);
			}
		}
	}

}
