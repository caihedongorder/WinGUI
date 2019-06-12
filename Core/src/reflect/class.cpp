#include "class.h"
#include <assert.h>
#include "class_impl.h"

namespace Core
{
	 void Class::AddFunction(const std::string& InFunctionName, std::shared_ptr<ClassFunctionBase> InProp)
	{
		 assert(mFuncs.find(InFunctionName) == mFuncs.end());
		 mFuncs[InFunctionName] = InProp;
	}

	Core::ClassFunctionBase* Class::FindFunction(const std::string& InFunctionName)
	{
		auto It = mFuncs.find(InFunctionName);
		if (It != mFuncs.end())
			return It->second.get();
		return nullptr;
	}


	void Class::AddProperty(const std::string& InPropName, std::shared_ptr<ClassProperty> InProp)
	{
		assert(mProps.find(InPropName) == mProps.end());
		mProps[InPropName] = InProp;
	}
	const ClassProperty* Class::FindProp(const std::string& InPropName) const {
		auto It = mProps.find(InPropName);
		if (It != mProps.end())
			return It->second.get();
		return nullptr;
	}
}
