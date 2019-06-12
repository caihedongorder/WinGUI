#pragma once
#include <typedefines.h>
#include <memory>
#include <windows/WindowBase.h>

namespace WinGUI
{
	template<typename App>
	class AppWrapper
	{
	public:
		AppWrapper()
		{
			_app = std::make_shared<App>();
			_app->OnInit();
		}
		~AppWrapper()
		{
			_app->OnUnInit();
		}

		App* operator->() {
			return _app.get();
		}
	private:
		std::shared_ptr<App> _app;
	};
	
	class WinBase;

	class WIN_GUI_API ApplicationBase
	{
		//friend class AppWrapper;
	public:
		ApplicationBase();
		virtual ~ApplicationBase();

		template<typename WinClass,typename... Params>
		WinClass* CreateTopWindow(Params ...params) {
			auto win = std::make_shared<WinClass>(params...);
			win->Create();
			mWindows.push_back(win);
			return (WinClass*)win.get();
		}

		void SetMainFrameWindow(HWND InMainFrameHandle);

		void Run();


		virtual bool OnInit();
		virtual void OnUnInit();
	public:

		/* event ....*/
		virtual void OnCloseWindow(HWND InHandle);

		void Event_Button_OnClick(HWND InHandle, u32 InCtrlId);

		void Event_ComboBox_SelChange(HWND InHandle, u32 InCtrlId);

		/* event ....*/
	public:
		template<typename WinClass>
		WinClass* FindSubWindow(HWND InHandle, u32 InCtrlId)
		{
			auto pos = std::find_if(mWindows.begin(), mWindows.end(), [InHandle](const auto& InWindow) {
				return InWindow->GetHandle() == InHandle;
			});
			if (pos != mWindows.end())
			{
				if (TopWindow* topWin = (TopWindow*)(*pos).get())
				{
					auto CtrlHandle = ::GetDlgItem(InHandle, InCtrlId);
					if (CtrlHandle != NULL)
					{
						return topWin->FindSubWindow<WinClass>(CtrlHandle);
					}
				}
			}
			return nullptr;
		}
	protected:
		std::list<std::shared_ptr<WinBase>> mWindows;
	};


}