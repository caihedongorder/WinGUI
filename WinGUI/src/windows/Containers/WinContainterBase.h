#pragma once
#include <windows/WindowBase.h>
#include <list>
#include <map>
#include <assert.h>
#include <unordered_map>
#include <windows/Controls/buttons/RadioButton.h>

namespace WinGUI
{
	class WIN_GUI_API WinContainerBase : public WinBase
	{
	public:
		typedef WinBase SuperClass;
		enum EWT { ID = EWindowType_WinBase };
	public:
		using WinBase::WinBase;

		template<typename WinClass,typename... Params>
		std::shared_ptr<WinClass> CreateSubWindow(const std::string& InCtrlName,Params... params)
		{
			std::shared_ptr<WinClass> createdWin;
			assert(mWindows.find(InCtrlName) == mWindows.end());
			createdWin = std::make_shared<WinClass>(params...);
			mWindows[InCtrlName] = createdWin;

			return createdWin;
		}
		template<typename WinClass>
		WinClass* FindSubWindow(const std::string& InCtrlName) {
			auto It = mWindows.find(InCtrlName);
			if (It != mWindows.end())
			{
				return (WinClass*)It->second.get();
			}
			return nullptr;
		}
		template<typename WinClass>
		WinClass* FindSubWindow(HWND InHandle) {
			for (auto It = mWindows.begin(); It != mWindows.end(); ++It)
			{
				if (It->second->GetHandle() == InHandle)
				{
					return (WinClass*)It->second.get();
				}
			}
			return nullptr;
		}

		RadioButtonGroup& CreateRadioButtonGroup(const std::string& InGroupName) {
			auto rbGroup = std::make_shared<RadioButtonGroup>(this);
			mRadioButtonGroups[InGroupName] = rbGroup;
			return *rbGroup;
		}

		std::string GetUniqueCtrlName(const std::string& InSuffix) const {
			auto uniqueName = InSuffix;
			auto i = 1;
			while (mWindows.find(uniqueName) != mWindows.end())
			{
				uniqueName = InSuffix;
				uniqueName += i++;
			}
			return uniqueName;
		}

	protected:
		std::unordered_map<std::string,std::shared_ptr<WinBase>> mWindows;

		std::unordered_map<std::string, std::shared_ptr<RadioButtonGroup>> mRadioButtonGroups;
	};
}
