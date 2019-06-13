#pragma once
#include <string>

namespace Core
{
	class ClassFunctionBase
	{
	public:
		ClassFunctionBase(void** InFunc) 
		{
			memcpy(mFunc, InFunc, sizeof(mFunc));
		}
		~ClassFunctionBase() {}

		std::string GetFuncDef() const { return mFuncDef; }
		std::string GetName() const { return mClassName; }

		template<typename Func>
		Func GetFunctionPtr() const {
			Func func;
			memcpy(&func, &mFunc, sizeof(func));
			return func;
		}

		template<typename Obj,typename returnValue>
		returnValue Call(Obj* InObject) const {
			typedef returnValue( Obj::*Func)();
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)();
		}
		template<typename Obj, typename returnValue,typename Param1>
		returnValue Call(Obj* InObject, Param1 InParam1) const {
			typedef returnValue(Obj::*Func)(Param1);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2) const {
			typedef returnValue(Obj::*Func)(Param1,Param2);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5,Param6);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5,InParam6);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5,Param6,Param7);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8,InParam9);
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9,typename Param10>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9,Param10 InParam10) const {
			typedef returnValue(Obj::*Func)(Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10);
			auto pFunc = GetFunctionPtr<Func>();
			return (((Obj*)InObject)->*pFunc)(InParam1,InParam2,InParam3,InParam4,InParam5,InParam6,InParam7,InParam8,InParam9,InParam10);
		}
	protected:
		std::string mClassName;
		std::string mFuncDef;
		i8 mFunc[sizeof(void*)];
	};


	template<typename Class, typename Func, typename returnValue>
	class ClassFunction : public ClassFunctionBase
	{
	public:
		ClassFunction(Func InFunc)
			:ClassFunctionBase((void**)&InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
		}
	};
}
