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
		friend class ReflectSystemImpl;
	public:
		Class(const std::string& InClassName,const std::string& InSuperClassName) 
			:mName(InClassName)
			,mSuperClassName(InSuperClassName)
			,mSuperClass(nullptr)
		{
		}
		virtual std::string GetName() const { return mName; };
		virtual std::string GetSuperClassName() const override { return mSuperClassName; }
		virtual IClass* GetSuperClass() const override { return mSuperClass; }
		virtual bool IsDerivedFrom(const IClass* InClass) const;


		virtual void AddProperty(const std::string& InPropName, std::shared_ptr<ClassProperty> InProp) override;
		virtual const ClassProperty* FindProp(const std::string& InPropName) const override;
		virtual void AddFunction(const std::string& InFunctionName, std::shared_ptr<ClassFunctionBase> InProp) override;
		virtual ClassFunctionBase* FindFunction(const std::string& InFunctionName) override;
	private:
		void SetSuperClass(IClass *InSuprClass) {
			mSuperClass = InSuprClass;
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<ClassProperty>> mProps;
		std::unordered_map<std::string, std::shared_ptr<ClassFunctionBase>> mFuncs;
		std::string mName;
		std::string mSuperClassName;
		IClass* mSuperClass;
	};
}

