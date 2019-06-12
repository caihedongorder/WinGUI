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
}

