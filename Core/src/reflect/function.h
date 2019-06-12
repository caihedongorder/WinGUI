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
