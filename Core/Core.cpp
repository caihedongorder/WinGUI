// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "reflect/reflectSystem.h"


namespace Core
{
	void Init()
	{
		IReflectSystem::GetInst()->Init();
	}
	void UnIint()
	{
		IReflectSystem::GetInst()->UnInit();
	}
}

