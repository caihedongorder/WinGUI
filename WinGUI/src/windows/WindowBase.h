#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include <memory>
#include <string>
#include <list>
#include <typedefines.h>
#include <functional>
#include <reflect/object.h>
#include <reflect/reflectSystem.h>

namespace WinGUI
{
	class WIN_GUI_API WinBase : public Core::Object
	{
		DECLARE_OBJECT(WIN_GUI_API, WinBase, Core::Object)
	public:
		WinBase(u32 InPosX,u32 InPosY,u32 InSizeX,u32 InSizeY,class TopWindow* InTopWindow,HWND InParentHandle = NULL);
		virtual ~WinBase();
		HWND GetHandle() const { return hwnd; }

		bool Create();

		void Show();
		void Hide();
		
		class TopWindow* GetTopWindow() { return mTopWindow; }

		template<typename TargetClass>
		bool CanCast(u32 InWinType)
		{
			if (InWinType == TargetClass::ID)
			{
				return true;
			}
#if 0
			if (ClassA::ID == ClassB::ID)
			{
				return true;
			}
			else
			{
				return CanCast<ClassA,ClassB::SuperClass>();
			}
#endif
		}

	protected:
		virtual bool OnCreate() { return false; }
	protected:
		class TopWindow* mTopWindow;
		HWND hwnd;
		HWND mParentHandle;
		u32 WinPosX = 0;
		u32 WinPosY = 0;
		u32 WinSizeX = 0;
		u32 WinSizeY = 0;
	};
	
	template class WIN_GUI_API std::shared_ptr<WinBase>;
}
