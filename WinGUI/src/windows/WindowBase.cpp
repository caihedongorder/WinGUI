#include "WindowBase.h"

namespace WinGUI
{
	IMPLEMENT_OBJECT_BEGIN(WinBase, Core::Object)
	IMPLEMENT_OBJECT_END()

	WinBase::WinBase(u32 InPosX, u32 InPosY, u32 InSizeX, u32 InSizeY, class TopWindow* InTopWindow,HWND InParentHandle)
		:
		WinPosX(InPosX),
		WinPosY(InPosY),
		WinSizeX(InSizeX),
		WinSizeY(InSizeY),
		mTopWindow(InTopWindow),
		mParentHandle(InParentHandle)
	{

	}

	WinBase::~WinBase()
	{
		DestroyWindow(hwnd);
		hwnd = NULL;
	}

	bool WinBase::Create()
	{
		return OnCreate();
	}

	void WinBase::Show()
	{
		::ShowWindow(hwnd, SW_SHOW);
	}

	void WinBase::Hide()
	{
		::ShowWindow(hwnd, SW_HIDE);
	}

}
