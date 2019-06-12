#include <windows.h>
#include <map>
#include <memory>
#include "WindowBase.h"
#include "apps/Application.h"

namespace WinGUI
{
#define CLASS_NAME TEXT("MyWndClass")
	
	HWND GMainFrameHandle = NULL;
	std::map<HWND, std::shared_ptr<WinBase>> GAllWindows;
	ApplicationBase* GApp = nullptr;

	LRESULT CALLBACK WindowProc(
		 HWND   hwnd,
		 UINT   uMsg,
		 WPARAM wParam,
		 LPARAM lParam
	)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			{
				GApp->OnCloseWindow(hwnd);
				return 0;
			}
			break;
		case  WM_COMMAND:
		{
			auto ControlId = LOWORD(wParam);
			auto notificatioin_code = HIWORD(wParam);
			if (notificatioin_code==BN_CLICKED)
			{
				GApp->Event_Button_OnClick(hwnd, ControlId);
			}
			else if (notificatioin_code == CBN_SELCHANGE)
			{
				GApp->Event_ComboBox_SelChange(hwnd, ControlId);
			}
		}
			break;
		default:
			break;
		}
		return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	BOOL RegisterWinClass() {
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = WindowProc;
		wc.cbWndExtra = 0;
		wc.style = 0;
		wc.cbClsExtra = 0;
		wc.hInstance = NULL;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = CLASS_NAME;
		wc.hIconSm = NULL;

		if (!RegisterClassEx(&wc))
			return FALSE;

		return  TRUE;
	}
}