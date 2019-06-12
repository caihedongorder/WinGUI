#pragma once
#include <reflect/class.h>
#include <memory>
#include <map>
#include <string>
#include <unordered_map>

namespace Core
{
	class Class : public IClass
	{
	public:
		Class(const std::string& InClassName) 
			:mName(InClassName)
		{
		}
		virtual std::string GetName() const { return mName; };
		virtual void AddProperty(const std::string& InPropName, std::shared_ptr<ClassProperty> InProp) override;
		virtual const ClassProperty* FindProp(const std::string& InPropName) const override;
		virtual void AddFunction(const std::string& InFunctionName, std::shared_ptr<ClassFunctionBase> InProp) override;
		virtual const ClassFunctionBase* FindFunction(const std::string& InFunctionName) const override;
	private:
		std::unordered_map<std::string, std::shared_ptr<ClassProperty>> mProps;
		std::unordered_map<std::string, std::shared_ptr<ClassFunctionBase>> mFuncs;
		std::string mName;
	};
}

