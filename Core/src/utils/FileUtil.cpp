#include "FileUtil.h"
#include <Core.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iterator>

namespace Core
{
	bool FileHelper::ReadFile(const std::wstring& InFilePath, std::vector<char>& outFileContent)
	{
		std::ifstream file(InFilePath);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			auto size = i32(file.tellg());
			file.seekg(0, std::ios::beg);

			outFileContent.resize(size);
			file.read(outFileContent.data(), size);

			return true;
		}

		return false;
	}

	bool FileHelper::ReadTextContent(const std::wstring& InFilePath, std::wstring& outTextContent)
	{
		std::vector<char> FileContent;
		if (FileHelper::ReadFile(InFilePath,FileContent))
		{
			auto unicodeSize = ::MultiByteToWideChar(CP_UTF8, NULL, FileContent.data(), i32(FileContent.size()), NULL, 0);

			std::vector<wchar_t> fileContent;
			fileContent.resize(unicodeSize);

			::MultiByteToWideChar(CP_UTF8, NULL, FileContent.data(), i32(FileContent.size()), fileContent.data(), i32(fileContent.size()));

			std::wostringstream oSS;
			std::copy(fileContent.cbegin(), fileContent.cend(), std::ostream_iterator<wchar_t, wchar_t>(oSS));
			outTextContent = oSS.str();

			return true;
		}

		return false;
	}

}