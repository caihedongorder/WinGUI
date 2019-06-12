#pragma once
#include <string>
#include <reflect/class.h>

namespace Core
{
	class CORE_API IReflectSystem
	{
	public:
		static IReflectSystem* GetInst();
		virtual IClass* RegisterClass(const std::string& InClassName) = 0;
		virtual IClass* FindClass(const std::string& InClassName) = 0;
		virtual void Init() = 0;
		virtual void UnInit() = 0;
	};
}

#define DECLARE_OBJECT(ClassPrefix,ThisClass, SuperClass)\
public:\
	static IClass* StaticClass();\
	IClass* GetClass() { return _PrivateClass; } \
	ThisClass();\
private:\
	class ClassPrefix ClassRegister\
	{\
	public:\
		ClassRegister(const std::string& InThisClassName,const std::string& InSuperClassName);\
		IClass* GetClass() { return mClass;}\
	private:\
		IClass* mClass;\
	};\
	static ClassRegister __msRegister;\
	IClass* _PrivateClass = nullptr;

#define IMPLEMENT_OBJECT_BEGIN(ThisClass, SuperClass)\
	ThisClass::ClassRegister ThisClass::__msRegister(FPropertyTag<ThisClass>::Inner.GetName(),FPropertyTag<SuperClass>::Inner.GetName());\
	IClass* ThisClass::StaticClass(){\
		return __msRegister.GetClass();\
	}\
	ThisClass::ThisClass(){\
		_PrivateClass = ThisClass::StaticClass();\
	}\
	ThisClass::ClassRegister::ClassRegister(const std::string& InThisClassName,const std::string& InSuperClassName)\
	{\
		mClass = Core::IReflectSystem::GetInst()->RegisterClass(InThisClassName);

#define IMPLEMENT_OBJECT_END() }

#define DEFINE_PROPERTY(ThisClass,PropertyName) mClass->AddPropertyT<ThisClass, decltype(ThisClass::PropertyName)>(#PropertyName, IClass::GetPropOffset(&C::PropertyName));

#define DEFINE_FUNCTION(ThisClass,returnValue,FunctionName) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunction<ThisClass, decltype(pFunc), returnValue> >(&ThisClass::FunctionName));\
}


