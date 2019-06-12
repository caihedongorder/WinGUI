#pragma once
#include <Core.h>
#include <string>
#include <vector>
#include <memory>

namespace Core
{
	class CORE_API CSVParser
	{
	public:
		static std::shared_ptr<CSVParser> Create(const std::wstring& InFilePath);
	public:
		std::vector<std::vector<std::wstring>> datas;
	};
}
