#include "reflectSystem.h"
#include <unordered_map>
#include <memory>
#include <assert.h>
#include "class_impl.h"

namespace Core
{
	class ReflectSystemImpl : public IReflectSystem
	{
	public:
		virtual IClass* RegisterClass(const std::string& InClassName) {
			assert(mClasses.find(InClassName) == mClasses.end());
			auto pClass = std::make_shared<Class>(InClassName);
			mClasses[InClassName] = pClass;
			return pClass.get();
		}
		virtual IClass* FindClass(const std::string& InClassName) {
			auto It = mClasses.find(InClassName);
			if (It != mClasses.end())
				return It->second.get();
			return nullptr;
		}

		virtual void Init() {

		}
		virtual void UnInit() {

		}
	private:
		std::unordered_map<std::string, std::shared_ptr<Class>> mClasses;
	};

	static IReflectSystem* GReflectSystem = nullptr;
	IReflectSystem* IReflectSystem::GetInst()
	{
		if (!GReflectSystem)
			GReflectSystem = new ReflectSystemImpl;
		return GReflectSystem;
	}
}