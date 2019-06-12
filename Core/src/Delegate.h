#pragma once
#include <list>
#include <memory>


namespace Core
{
	template<typename... ParamsType>
	class FDelegateInstance 
	{
	public:
		virtual void Execute(ParamsType... InParams) {}
	};

	typedef void(*DelegateFunc)();

	template<typename Func, typename... ParamsType>
	class FDelegateInstance_Func : public FDelegateInstance<ParamsType...>
	{
	public:
		FDelegateInstance_Func(Func InFunc)
			:mFunc(InFunc)
		{

		}

		virtual void Execute(ParamsType... InParams) override {
			mFunc(InParams...);
		}

	private:
		Func mFunc;
	};

	template<typename Class, typename ClassMethod, typename... ParamsType>
	class FDelegateInstance_ClassMethod : public FDelegateInstance<ParamsType...>
	{
	public:
		FDelegateInstance_ClassMethod(Class* InClassObj, ClassMethod InClassMethod)
			:mClassObj(InClassObj)
			, mClassMethod(InClassMethod)
		{

		}

		virtual void Execute(ParamsType... InParams) override {
			(mClassObj->*mClassMethod)(InParams...);
		}

	private:
		Class *mClassObj;
		ClassMethod mClassMethod;
	};


	template<typename retValue, typename... ParamsType>
	class TDelegate
	{
	public:

		void Broadcast(ParamsType... Params) {
			for (auto It = mDelegates.begin(); It != mDelegates.end(); ++It)
			{
				(*It)->Execute(Params...);
			}
		}

		template<typename Func>
		void AddStatic(Func InFunc) {
			mDelegates.push_back(std::make_shared<FDelegateInstance_Func<Func, ParamsType...>>(InFunc));
		}


		template<typename Class, typename ClassMethod>
		void AddClassMethod(Class* InClassObj, ClassMethod InClassMethod) {
			mDelegates.push_back(std::make_shared<FDelegateInstance_ClassMethod<Class, ClassMethod, ParamsType...>>(InClassObj, InClassMethod));
		}

		template<typename Lambda>
		void AddLambda(Lambda InFunc) {
			mDelegates.push_back(std::make_shared<FDelegateInstance_Func<Lambda, ParamsType...>>(InFunc));
		}

	private:
		std::list<std::shared_ptr<FDelegateInstance<ParamsType...>>> mDelegates;
	};
}
