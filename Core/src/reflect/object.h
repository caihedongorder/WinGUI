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
		template<typename returnValue,typename Param1>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1>(this, InParam1);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2>(this, InParam1,InParam2);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3>(this, InParam1,InParam2,InParam3);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4>(this, InParam1,InParam2,InParam3,InParam4);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5>(this, InParam1,InParam2,InParam3,InParam4,InParam5);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5,Param6>(this, InParam1,InParam2,InParam3,InParam4,InParam5,InParam6);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5,Param6,Param7>(this, InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8>(this, InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9>(this, InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8,InParam9);
			}
			return returnValue();
		}
		template<typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9,typename Param10>
		returnValue CallFunction(const std::string& InFuncName,Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9,Param10 InParam10) {
			if (auto pFunc = GetClass()->FindFunction(InFuncName))
			{
				return pFunc->Call<Object, returnValue, Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10>(this, InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8,InParam9,InParam10);
			}
			return returnValue();
		}
	};
}
