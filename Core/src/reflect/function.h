#pragma once
#include <string>
#include <vector>

namespace Core
{
	class FunctionArgContentBase {
	public:
		FunctionArgContentBase() {}
		virtual ~FunctionArgContentBase() {}
		virtual bool IsValid() { return true; }
	};

	class FunctionArgContentNone : public FunctionArgContentBase {
	public:
		template<typename P>
		FunctionArgContentNone(P InValue)
		{

		}
		virtual bool IsValid() { return false; }
	};

	template<typename T>
	class TFunctionArgContent : public FunctionArgContentBase
	{
	public:
		template<typename P>
		TFunctionArgContent(P InValue) 
			:Value(T(InValue))
		{
		
		}
		TFunctionArgContent() 
			:Value()
		{

		}
		T GetValue() { return Value; }
		void SetValue(T InValue) { Value = InValue; }

	private:
		T Value;
	};

	template<typename T>
	class TFunctionArgContent<T&> : public FunctionArgContentBase
	{
	public:
		TFunctionArgContent(T& InValue)
			:Value(InValue)
		{

		}
		T& GetValue() { return Value; }

	private:
		T& Value;
	};

	template<>
	class TFunctionArgContent<void> : public FunctionArgContentBase
	{
	public:
		TFunctionArgContent()
		{

		}
		virtual bool IsVoid() { return true; }

		void SetValue(void) {}
	};

	class FunctionArg
	{
	public:
		FunctionArg(FunctionArgContentBase* InContent) {
			mContent = InContent;
		}
		~FunctionArg() {
			if (mContent)
			{
				delete mContent;
				mContent = nullptr;
			}
		}
		FunctionArgContentBase* GetContent() { return mContent; }

	private:
		FunctionArgContentBase* mContent;
	};

	class FunctionParamBase
	{
	public:
		FunctionParamBase() {}
		virtual ~FunctionParamBase() {}

		ClassPropertyType GetType() const { return mType; }
		bool IsReference() const { return mIsReferene; }
	protected:
		ClassPropertyType mType;
		bool mIsReferene = false;
	};

	template<typename T>
	class TFunctionParam;

	template<>
	class TFunctionParam<i8> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_I8;
		}
	};

	template<>
	class TFunctionParam<i16> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_I16;
		}
	};

	template<>
	class TFunctionParam<i32> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_I32;
		}
	};
	template<>
	class TFunctionParam<i64> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_I32;
		}
	};


	template<>
	class TFunctionParam<f32> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_F32;
		}
	};

	template<>
	class TFunctionParam<f32&> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_F32;
			mIsReferene = true;
		}
	};


	template<>
	class TFunctionParam<f64> : public FunctionParamBase
	{
	public:
		TFunctionParam()
		{
			mType = ClassPropertyType_F64;
		}
	};
	
	template<typename Param, ClassPropertyType PropType,bool IsReference>
	struct TFunctionArgContentSelector { typedef FunctionArgContentNone ContentType; };

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I8,false>
	{
		typedef TFunctionArgContent<i8> ContentType;
	};
	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I8,true>
	{
		typedef TFunctionArgContent<i8&> ContentType;
	};

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I16,false>
	{
		typedef TFunctionArgContent<i16> ContentType;
	};
	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I16,true>
	{
		typedef TFunctionArgContent<i16&> ContentType;
	};

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I32,false>
	{
		typedef TFunctionArgContent<i32> ContentType;
	};
	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I32,true>
	{
		typedef TFunctionArgContent<i32&> ContentType;
	};


	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I64,false>
	{
		typedef TFunctionArgContent<i64> ContentType;
	};
	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_I64,true>
	{
		typedef TFunctionArgContent<i64&> ContentType;
	};


	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_F32,false>
	{
		typedef TFunctionArgContent<f32> ContentType;
	};

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_F32,true>
	{
		typedef TFunctionArgContent<f32&> ContentType;
	};

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_F64,false>
	{
		typedef TFunctionArgContent<f64> ContentType;
	};

	template<typename Param>
	struct TFunctionArgContentSelector<Param, ClassPropertyType_F64,true>
	{
		typedef TFunctionArgContent<f64&> ContentType;
	};

	template<typename Param>
	std::shared_ptr<FunctionArg> NewFuntionArg(std::shared_ptr<FunctionParamBase> InParam,Param InArgValue) {
		auto InType = InParam->GetType();
		auto InIsReferece = InParam->IsReference();
		if (InType == ClassPropertyType_I8)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I8, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I8, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param,i8&>::value>::Type(InArgValue));
			}
		}
		else if (InType == ClassPropertyType_I16)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I16, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I16, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param, i16&>::value>::Type(InArgValue));
			}
		}
		else if (InType == ClassPropertyType_I32)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I32, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I32, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param, i32&>::value>::Type(InArgValue));
			}
		}
		else if (InType == ClassPropertyType_I64)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I64, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_I64, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param, i64&>::value>::Type(InArgValue));
			}
		}
		else if (InType == ClassPropertyType_F32)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_F32, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_F32, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param, f32&>::value>::Type(InArgValue));
			}
		}
		else if (InType == ClassPropertyType_F64)
		{
			if (!InIsReferece)
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_F64, false>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					FTypeIsNumber<Param>::Value>::Type(InArgValue));
			}
			else
			{
				return std::make_shared<FunctionArg>(new typename TSelectType<typename TFunctionArgContentSelector<Param, ClassPropertyType_F64, true>::ContentType,
					typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown, false>::ContentType,
					std::is_same<Param, f64&>::value>::Type(InArgValue));
			}
		}
		return std::make_shared<FunctionArg>(new typename TFunctionArgContentSelector<Param, ClassPropertyType_Unknown,false>::ContentType(InArgValue));
	}


	class ClassFunctionBase
	{
	public:
		ClassFunctionBase() 
		{
		}
		~ClassFunctionBase() {}

		std::string GetFuncDef() const { return mFuncDef; }
		std::string GetName() const { return mClassName; }
		

		template<typename Obj>
		void SetObj(Obj* InObj) { mObj = InObj;	}
		
	
		template<typename returnValue>
		returnValue GetReturnValue() {
			returnValue retValue = ((TFunctionArgContent<returnValue>*) mReturnValue->GetContent())->GetValue();
			return retValue;
		}

		template<>
		void GetReturnValue<void>() {}

		template<typename Obj,typename returnValue>
		returnValue Call(Obj* InObject) {
			this->BeginCall();
			this->SetObj(InObject);
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1>
		returnValue Call(Obj* InObject, Param1 InParam1)  {

			this->BeginCall();
			if (mParams.size() == 1)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2)  {
			this->BeginCall();
			if (mParams.size() == 2)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3)  {
			this->BeginCall();
			if (mParams.size() == 3)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4)  {
			this->BeginCall();
			if (mParams.size() == 4)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5)  {
			this->BeginCall();
			if (mParams.size() == 5)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6)  {
			this->BeginCall();
			if (mParams.size() == 6)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->AddArg(NewFuntionArg<Param6>(mParams[5], InParam6));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7)  {
			this->BeginCall();
			if (mParams.size() == 7)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->AddArg(NewFuntionArg<Param6>(mParams[5], InParam6));
				this->AddArg(NewFuntionArg<Param7>(mParams[6], InParam7));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8)  {
			this->BeginCall();
			if (mParams.size() == 8)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->AddArg(NewFuntionArg<Param6>(mParams[5], InParam6));
				this->AddArg(NewFuntionArg<Param7>(mParams[6], InParam7));
				this->AddArg(NewFuntionArg<Param8>(mParams[7], InParam8));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9)  {
			this->BeginCall();
			if (mParams.size() == 9)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->AddArg(NewFuntionArg<Param6>(mParams[5], InParam6));
				this->AddArg(NewFuntionArg<Param7>(mParams[6], InParam7));
				this->AddArg(NewFuntionArg<Param8>(mParams[7], InParam8));
				this->AddArg(NewFuntionArg<Param9>(mParams[8], InParam9));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9,typename Param10>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9,Param10 InParam10)  {
			this->BeginCall();
			if (mParams.size() == 10)
			{
				this->AddArg(NewFuntionArg<Param1>(mParams[0], InParam1));
				this->AddArg(NewFuntionArg<Param2>(mParams[1], InParam2));
				this->AddArg(NewFuntionArg<Param3>(mParams[2], InParam3));
				this->AddArg(NewFuntionArg<Param4>(mParams[3], InParam4));
				this->AddArg(NewFuntionArg<Param5>(mParams[4], InParam5));
				this->AddArg(NewFuntionArg<Param6>(mParams[5], InParam6));
				this->AddArg(NewFuntionArg<Param7>(mParams[6], InParam7));
				this->AddArg(NewFuntionArg<Param8>(mParams[7], InParam8));
				this->AddArg(NewFuntionArg<Param9>(mParams[8], InParam9));
				this->AddArg(NewFuntionArg<Param10>(mParams[9], InParam9));
				this->SetObj(InObject);
				this->Invoke();
			}
			this->EndCall();
			return GetReturnValue<returnValue>();
		}

		template<typename T>
		TFunctionArgContent<T>* GetArg(i32 iParam) {
			return (TFunctionArgContent<T>*)mArgs[iParam]->GetContent();
		}
		i32 GetNumsArg() const { return i32(mArgs.size()); }
		bool IsAllArgValid() {
#if _DEBUG
			for (auto iArg = 0 ; iArg < mArgs.size() ; ++iArg)
			{
				if (!mArgs[iArg]->GetContent()->IsValid())
				{
					return false;
				}
			}
#endif
			return true;
		}

	protected:
		virtual void Invoke() = 0;

	
	private:
		void BeginCall() { mArgs.clear(); }
		void EndCall() { mArgs.clear(); }
		void AddArg(std::shared_ptr<FunctionArg> InArg) { mArgs.push_back(InArg); }
	protected:
		std::string mClassName;
		std::string mFuncDef;
		void* mObj = nullptr;

		std::vector<std::shared_ptr<FunctionParamBase>> mParams;
		std::vector<std::shared_ptr<FunctionArg>> mArgs;
		std::shared_ptr<FunctionArg> mReturnValue;
	};


	template<typename Class, typename Func, typename returnValue>
	class ClassFunction : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				(((Class*)InObj)->*InFunc)();
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				pRetContent->SetValue((((Class*)InObj)->*InFunc)());
			}
		};

	public:
		ClassFunction(Func InFunc)
			:ClassFunctionBase()
			,mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj,mFunc,mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue,typename Param1>
	class ClassFunctionOneParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 1 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction,Func InFunc,std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 1 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue()));
				}
			}
		};

	public:
		ClassFunctionOneParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();

			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj,this,mFunc,mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1,typename Param2>
	class ClassFunctionTwoParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 2 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(),pParam2->GetValue());
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 2 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(),pParam2->GetValue()));
				}
			}
		};

	public:
		ClassFunctionTwoParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};
	
	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2,typename Param3>
	class ClassFunctionThreeParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 3 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(),pParam3->GetValue());
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 3 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue() ));
				}
			}
		};

	public:
		ClassFunctionThreeParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3,typename Param4>
	class ClassFunctionFourParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 4 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue());
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 4 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue()));
				}
			}
		};

	public:
		ClassFunctionFourParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4,typename Param5>
	class ClassFunctionFiveParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 5 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 5 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(),pParam5->GetValue() ));
				}
			}
		};

	public:
		ClassFunctionFiveParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5,typename Param6>
	class ClassFunctionSixParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 6 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 6 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue() ));
				}
			}
		};

	public:
		ClassFunctionSixParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param6>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6,typename Param7>
	class ClassFunctionSevenParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 7 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 7 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue()));
				}
			}
		};

	public:
		ClassFunctionSevenParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param6>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param7>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};

	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7,typename Param8>
	class ClassFunctionEightParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 8 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 8 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue()));
				}
			}
		};

	public:
		ClassFunctionEightParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param6>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param7>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param8>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};


	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7, typename Param8, typename Param9>
	class ClassFunctionNineParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 9 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					auto pParam9 = InFunction->GetArg<Param9>(8);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue(), pParam9->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 9 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					auto pParam9 = InFunction->GetArg<Param9>(8);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue(), pParam9->GetValue() ));
				}
			}
		};

	public:
		ClassFunctionNineParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param6>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param7>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param8>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param9>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};


	template<typename Class, typename Func, typename returnValue, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6, typename Param7, typename Param8, typename Param9, typename Param10>
	class ClassFunctionTenParam : public ClassFunctionBase
	{
		template<bool VoidRT>
		class FunctionInvoker;

		template<>
		class FunctionInvoker<true>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<void>());
				if (InFunction->GetNumsArg() == 10 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					auto pParam9 = InFunction->GetArg<Param9>(8);
					auto pParam10 = InFunction->GetArg<Param10>(9);
					(((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue(), pParam9->GetValue() ,pParam10->GetValue() );
				}
			}
		};
		template<>
		class FunctionInvoker<false>
		{
		public:
			FunctionInvoker(Class* InObj, ClassFunctionBase* InFunction, Func InFunc, std::shared_ptr<FunctionArg>& OutRetValue) {
				OutRetValue = std::make_shared<FunctionArg>(new TFunctionArgContent<returnValue>());
				auto pRetContent = (TFunctionArgContent<returnValue>*)OutRetValue->GetContent();
				if (InFunction->GetNumsArg() == 10 && InFunction->IsAllArgValid())
				{
					auto pParam1 = InFunction->GetArg<Param1>(0);
					auto pParam2 = InFunction->GetArg<Param2>(1);
					auto pParam3 = InFunction->GetArg<Param3>(2);
					auto pParam4 = InFunction->GetArg<Param4>(3);
					auto pParam5 = InFunction->GetArg<Param5>(4);
					auto pParam6 = InFunction->GetArg<Param6>(5);
					auto pParam7 = InFunction->GetArg<Param7>(6);
					auto pParam8 = InFunction->GetArg<Param8>(7);
					auto pParam9 = InFunction->GetArg<Param9>(8);
					auto pParam10 = InFunction->GetArg<Param10>(9);
					pRetContent->SetValue((((Class*)InObj)->*InFunc)(pParam1->GetValue(), pParam2->GetValue(), pParam3->GetValue(), pParam4->GetValue(), pParam5->GetValue(), pParam6->GetValue(), pParam7->GetValue(), pParam8->GetValue(), pParam9->GetValue(), pParam10->GetValue() ));
				}
			}
		};

	public:
		ClassFunctionTenParam(Func InFunc)
			:ClassFunctionBase()
			, mFunc(InFunc)
		{
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mFuncDef = typeid(Func).name();
			mParams.push_back(std::make_shared<TFunctionParam<Param1>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param2>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param3>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param4>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param5>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param6>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param7>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param8>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param9>>());
			mParams.push_back(std::make_shared<TFunctionParam<Param10>>());
		}

		Func GetFunctionPtr() { return mFunc; }
	protected:
		virtual void Invoke() {
			FunctionInvoker<TIsVoid<returnValue>::Value> Invoker((Class*)mObj, this, mFunc, mReturnValue);
		}
	private:
		Func mFunc;
	};
}
