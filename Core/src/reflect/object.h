#pragma once
#include "Core.h"
#include <reflect/class.h>
#include <reflect/reflectSystem.h>


namespace Core
{

	class CORE_API Object
	{
		DECLARE_OBJECT(CORE_API,Object,Object)
	public:
		template<typename T>
		T GetValue(const std::string& InPropName) const {
			auto pClass = GetClass();
			if (auto pProperty = pClass->FindProp(InPropName))
			{
				return pProperty->GetValue<Object, T>(this);
			}
			return T();
		}

		template<typename T>
		void SetValue(const std::string& InPropName, T InValue) {
			if (auto pProperty = GetClass()->FindProp(InPropName))
			{
				pProperty->SetValue<Object, T>(this, InValue);
			}
		}

		template<typename returnValue>
		returnValue CallFunction(const std::string& InFuncName) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue>(this);
			}
			return returnValue();
		}
	};
}
