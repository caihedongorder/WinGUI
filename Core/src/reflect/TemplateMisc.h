#pragma once

namespace Core
{
	template<typename T>
	struct TIsReference
	{
		enum { Value = 0 };
	};

	template<typename T>
	struct TIsReference<T&>
	{
		enum { Value = 1 };
	};

	template<typename T>
	struct TIsVoid
	{
		enum { Value = 0 };
	};
	template<>
	struct TIsVoid<void>
	{
		enum { Value = 1 };
	};


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

	template<ClassPropertyType prop> struct FPropertyIsNumber { enum { Value = 0 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_I8> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_I16> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_I32> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_I64> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_U8> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_U16> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_U32> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_U64> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_F32> { enum { Value = 1 }; };
	template<> struct FPropertyIsNumber<ClassPropertyType_F64> { enum { Value = 1 }; };


	template<typename T> struct FTypeIsNumber { enum { Value = 0 }; };
	template<> struct FTypeIsNumber<i8> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<i16> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<i32> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<i64> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<u8> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<u16> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<u32> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<u64> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<f32> { enum { Value = 1 }; };
	template<> struct FTypeIsNumber<f64> { enum { Value = 1 }; };

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

	template<typename TA,typename TB,bool SelectA> struct TSelectType;
	template<typename TA, typename TB> struct TSelectType<TA, TB, true> { typedef TA Type; };
	template<typename TA, typename TB> struct TSelectType<TA, TB, false> { typedef TB Type; };

#if 0
	template<ClassPropertyType SrcProp1, ClassPropertyType TargetProp2>
	struct FPropertyConvertable { enum { Value = 0 }; };

	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_I8> { enum { Value = 1 }; };
	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_I16> { enum { Value = 1 }; };
	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_I32> { enum { Value = 1 }; };
	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_I64> { enum { Value = 1 }; };
	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_U8> { enum { Value = 1 }; };
	template<> struct FPropertyConvertable<ClassPropertyType_I8, ClassPropertyType_U16> { enum { Value = 1 }; };
#endif

}

