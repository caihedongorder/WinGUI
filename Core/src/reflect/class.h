#pragma once
#include <Core.h>
#include <string>
#include <memory>
#include <reflect/property.h>
#include <reflect/function.h>

namespace Core
{
	class CORE_API IClass
	{
	public:
		IClass() {}
		virtual ~IClass() {}

		virtual std::string GetName() const = 0;
		virtual void AddProperty(const std::string& InPropName, std::shared_ptr<ClassProperty> InProp) = 0;
		virtual const ClassProperty* FindProp(const std::string& InPropName) const = 0;
		virtual void AddFunction(const std::string& InFunctionName, std::shared_ptr<ClassFunctionBase> InProp) = 0;
		virtual const ClassFunctionBase* FindFunction(const std::string& InFunctionName) const = 0;


		template<typename C, typename prop>
		void AddPropertyT(const std::string& InPropName, i32 InOffset) {
			AddProperty(InPropName, std::make_shared<Property<C, prop>>(InOffset));
		}

		template<typename Prop>
		static i32 GetPropOffset(Prop InProp) {
			auto pA = InProp;
			auto ppA = (i32**)&pA;
			auto iOffset = i32(*ppA);
			return iOffset;
		}

	};

}
