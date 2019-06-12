#pragma once
#include <string>
#include <Core_Defines.h>
#include <reflect/TemplateMisc.h>
#include <utils/string_util.h>

namespace Core
{
	template<typename T>
	struct FPropertyTag
	{
		struct FPropertyTagInner
		{
			FPropertyTagInner()
			{
				Name = typeid(T).name();
				IsClass = StringUtil::StartWith(Name, "class");
				IsStruct = StringUtil::StartWith(Name, "struct");
			}
			std::string GetName() {
				return typeid(T).name();
			}
			std::string Name;
			bool IsClass;
			bool IsStruct;
		};
		static FPropertyTagInner Inner;
	};
	template<typename T> typename FPropertyTag<T>::FPropertyTagInner FPropertyTag<T>::Inner;


	enum ClassPropertyType
	{
		ClassPropertyType_Unknown,
		ClassPropertyType_I8,
		ClassPropertyType_I16,
		ClassPropertyType_I32,
		ClassPropertyType_I64,

		ClassPropertyType_U8,
		ClassPropertyType_U16,
		ClassPropertyType_U32,
		ClassPropertyType_U64,

		ClassPropertyType_F32,
		ClassPropertyType_F64,

		ClassPropertyType_Class,
		ClassPropertyType_Struct,
	};

	template<typename T>
	struct FPropertyType
	{
		enum { Value = ClassPropertyType_Unknown };
	};


	template<>
	struct FPropertyType<i8> { enum { Value = ClassPropertyType_I8 }; };

	template<>
	struct FPropertyType<i16> { enum { Value = ClassPropertyType_I16 }; };

	template<>
	struct FPropertyType<i32> { enum { Value = ClassPropertyType_I32 }; };

	template<>
	struct FPropertyType<i64> { enum { Value = ClassPropertyType_I64 }; };

	template<>
	struct FPropertyType<u8> { enum { Value = ClassPropertyType_U8 }; };

	template<>
	struct FPropertyType<u16> { enum { Value = ClassPropertyType_U16 }; };

	template<>
	struct FPropertyType<u32> { enum { Value = ClassPropertyType_U32 }; };

	template<>
	struct FPropertyType<u64> { enum { Value = ClassPropertyType_U64 }; };

	template<>
	struct FPropertyType<f32> { enum { Value = ClassPropertyType_F32 }; };

	template<>
	struct FPropertyType<f64> { enum { Value = ClassPropertyType_F64 }; };


	class ClassProperty
	{
	public:
		ClassProperty() {}
		virtual ~ClassProperty() {}

		std::string GetClassName() const { return mClassName; }
		std::string GetName() const { return mName; }
		virtual ClassPropertyType  GetType() const { return ClassPropertyType_Unknown; }

		template<typename Class, typename T>
		T GetValue(const Class* InObj) const {
			auto pData = (const i8*)((const void*)InObj);
			return T(*(T*)(pData + mOffset));
		}

		template<typename Class, typename T>
		void SetValue(Class* InObj, T InValue) const {
			auto pData = (i8*)((void*)InObj);
			*(T*)(pData + mOffset) = InValue;
		}

	protected:
		std::string mClassName;
		std::string mName;
		u32 mPropSize;
		i32 mOffset;
	};


	template<typename Class, typename T>
	class Property : public ClassProperty
	{
	public:
		Property(i32 InOffset)
		{
			static_assert(TIsReference<T>::Value == 0, "Class Member Variable can not be referenced");
			mClassName = FPropertyTag<Class>::Inner.GetName();
			mName = std::string(typeid(T).name());

			mPropSize = sizeof(T);
			mOffset = InOffset;
		}

		virtual ClassPropertyType  GetType() const override {
			if (FPropertyTag<T>::Inner.IsClass)
				return ClassPropertyType_Class;
			else if (FPropertyTag<T>::Inner.IsStruct)
				return ClassPropertyType_Struct;

			return (ClassPropertyType)FPropertyType<T>::Value;
		}
	};

}
