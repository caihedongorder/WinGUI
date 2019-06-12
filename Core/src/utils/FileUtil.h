#pragma once
#include <string>
#include <vector>
#include <Core.h>

namespace Core
{
	enum FileEncoding
	{
		FileEncoding_GBK,
		FileEncoding_UTF8,
	};

	class CORE_API FileHelper
	{
	public:
		static bool ReadFile(const std::wstring& InFilePath, std::vector<char>& outFileContent);
		static bool ReadTextContent(const std::wstring& InFilePath, std::wstring& outTextContent);
	};
}