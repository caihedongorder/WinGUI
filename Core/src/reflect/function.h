#pragma once
#include <string>

namespace Core
{
	class ClassFunctionBase
	{
	public:
		ClassFunctionBase() {}
		~ClassFunctionBase() {}

		std::string GetFuncDef() const { return mFuncDef; }
		std::string GetName() const { return mClassName; }
	protected:
		std::string mClassName;
		std::string mFuncDef;
	};


	template<typename Class, typename Func, typename returnValue>
	class ClassFunction : public ClassFunctionBase
	{
	public:
		ClassFunction(Func InFunc)
			:mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.Name;
			mFuncDef = typeid(Func).name();
		}

		returnValue Involve(void *InObj) {
			return (((Class*)InObj)->*mFunc)();
		}
	private:
		Func mFunc;
	};
}
