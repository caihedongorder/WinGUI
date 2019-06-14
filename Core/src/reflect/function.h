#pragma once
#include <string>
#include <vector>

namespace Core
{
	class FunctionArgContentBase {
	public:
		FunctionArgContentBase() {}
		virtual ~FunctionArgContentBase() {}
		virtual bool IsVoid() { return false; }
	};
	template<typename T>
	class TFunctionArgContent : public FunctionArgContentBase
	{
	public:
		TFunctionArgContent(T InValue) 
			:Value(InValue)
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
	};


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
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param6>(InParam6)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param6>(InParam6)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param7>(InParam7)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param6>(InParam6)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param7>(InParam7)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param8>(InParam8)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param6>(InParam6)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param7>(InParam7)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param8>(InParam8)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param9>(InParam9)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}
		template<typename Obj, typename returnValue,typename Param1,typename Param2,typename Param3,typename Param4,typename Param5,typename Param6,typename Param7,typename Param8,typename Param9,typename Param10>
		returnValue Call(Obj* InObject, Param1 InParam1,Param2 InParam2,Param3 InParam3,Param4 InParam4,Param5 InParam5,Param6 InParam6,Param7 InParam7,Param8 InParam8,Param9 InParam9,Param10 InParam10)  {
			this->BeginCall();
			this->SetObj(InObject);
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param1>(InParam1)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param2>(InParam2)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param3>(InParam3)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param4>(InParam4)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param5>(InParam5)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param6>(InParam6)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param7>(InParam7)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param8>(InParam8)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param9>(InParam9)));
			this->AddArg(std::make_shared<FunctionArg>(new TFunctionArgContent<Param10>(InParam10)));
			this->Invoke();
			this->EndCall();
			return GetReturnValue<returnValue>();
		}

		template<typename T>
		TFunctionArgContent<T>* GetArg(i32 iParam) {
			return (TFunctionArgContent<T>*)mArgs[iParam]->GetContent();
		}
		i32 GetNumsArg() const { return mArgs.size(); }

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
				if (InFunction->GetNumsArg() == 1)
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
				if (InFunction->GetNumsArg() == 1)
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
				if (InFunction->GetNumsArg() == 2)
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
				if (InFunction->GetNumsArg() == 2)
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
				if (InFunction->GetNumsArg() == 3)
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
				if (InFunction->GetNumsArg() == 3)
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
				if (InFunction->GetNumsArg() == 4)
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
				if (InFunction->GetNumsArg() == 4)
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
				if (InFunction->GetNumsArg() == 5)
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
				if (InFunction->GetNumsArg() == 5)
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
				if (InFunction->GetNumsArg() == 6)
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
				if (InFunction->GetNumsArg() == 6)
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
				if (InFunction->GetNumsArg() == 7)
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
				if (InFunction->GetNumsArg() == 7)
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
				if (InFunction->GetNumsArg() == 8)
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
				if (InFunction->GetNumsArg() == 8)
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
				if (InFunction->GetNumsArg() == 9)
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
				if (InFunction->GetNumsArg() == 9)
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
				if (InFunction->GetNumsArg() == 10)
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
				if (InFunction->GetNumsArg() == 10)
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
