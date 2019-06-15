#pragma once
#include <string>
#include <reflect/class.h>

namespace Core
{
	class CORE_API IReflectSystem
	{
	public:
		static IReflectSystem* GetInst();
		virtual IClass* RegisterClass(const std::string& InClassName,const std::string& InSuperClassName) = 0;
		virtual IClass* FindClass(const std::string& InClassName) = 0;
		virtual void Init() = 0;
		virtual void UnInit() = 0;
	};
}

#define DECLARE_OBJECT(ClassPrefix,ThisClass, SuperClass)\
public:\
	static Core::IClass* StaticClass();\
	virtual Core::IClass* GetClass() const { return ThisClass::StaticClass(); } \
	ThisClass();\
private:\
	class ClassPrefix ClassRegister\
	{\
	public:\
		ClassRegister(const std::string& InThisClassName,const std::string& InSuperClassName);\
		Core::IClass* GetClass() { return mClass;}\
	private:\
		Core::IClass* mClass;\
	};\
	static ClassRegister __msRegister;

#define IMPLEMENT_OBJECT_BEGIN(ThisClass, SuperClass)\
	ThisClass::ClassRegister ThisClass::__msRegister(Core::FPropertyTag<ThisClass>::Inner.GetName(),Core::FPropertyTag<SuperClass>::Inner.GetName());\
	Core::IClass* ThisClass::StaticClass(){\
		return __msRegister.GetClass();\
	}\
	ThisClass::ThisClass(){\
	}\
	ThisClass::ClassRegister::ClassRegister(const std::string& InThisClassName,const std::string& InSuperClassName)\
	{\
		mClass = Core::IReflectSystem::GetInst()->RegisterClass(InThisClassName,InSuperClassName);

#define IMPLEMENT_OBJECT_END() }

#define DEFINE_PROPERTY(ThisClass,PropertyName) mClass->AddPropertyT<ThisClass, decltype(ThisClass::PropertyName)>(#PropertyName, Core::IClass::GetPropOffset(&C::PropertyName));

#define DEFINE_FUNCTION(ThisClass,returnValue,FunctionName) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunction<ThisClass, decltype(pFunc), returnValue> >(&ThisClass::FunctionName));\
}

#define DEFINE_FUNCTION_ONE_PARAM(ThisClass,returnValue,FunctionName,Param1) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionOneParam<ThisClass, decltype(pFunc),returnValue,Param1> >(&ThisClass::FunctionName));\
}


#define DEFINE_FUNCTION_TWO_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionTwoParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2> >(&ThisClass::FunctionName));\
}
#define DEFINE_FUNCTION_THREE_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionThreeParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3> >(&ThisClass::FunctionName));\
}

#define DEFINE_FUNCTION_FOUR_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionFourParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4> >(&ThisClass::FunctionName));\
}
#define DEFINE_FUNCTION_FIVE_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionFiveParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5> >(&ThisClass::FunctionName));\
}

#define DEFINE_FUNCTION_SIX_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5,Param6) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionSixParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5,Param6> >(&ThisClass::FunctionName));\
}


#define DEFINE_FUNCTION_SEVEN_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5,Param6,Param7) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionSevenParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5,Param6,Param7> >(&ThisClass::FunctionName));\
}


#define DEFINE_FUNCTION_EIGHT_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionEightParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8> >(&ThisClass::FunctionName));\
}


#define DEFINE_FUNCTION_NINE_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionNineParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9> >(&ThisClass::FunctionName));\
}


#define DEFINE_FUNCTION_TEN_PARAM(ThisClass,returnValue,FunctionName,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10) {\
	auto pFunc = &ThisClass::FunctionName;\
	mClass->AddFunction(#FunctionName , std::make_shared< Core::ClassFunctionTenParam<ThisClass, decltype(pFunc),returnValue,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10> >(&ThisClass::FunctionName));\
}
