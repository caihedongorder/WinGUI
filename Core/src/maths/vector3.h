#pragma once
#include <Core.h>

namespace Core
{
	class CORE_API vector3
	{
	public:
		vector3(f32 ix, f32 iy, f32 iz);
	
	public:
		f32 x, y, z;
	};
}
