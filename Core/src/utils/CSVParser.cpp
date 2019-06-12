#include "CSVParser.h"
#include "FileUtil.h"
#include <sstream>
#include "string_util.h"
#include <iterator>

namespace Core
{
	std::shared_ptr<CSVParser> CSVParser::Create(const std::wstring& InFilePath)
	{
		auto csvParser = std::make_shared<CSVParser>();

		std::wstring fileContent;
		FileHelper::ReadTextContent(InFilePath, fileContent);

		std::vector<std::wstring> csvRows;
		std::wistringstream iSS(fileContent);

		std::copy(split_istream_iterator<std::wstring,wchar_t>(iSS,'\n'),
			split_istream_iterator<std::wstring,wchar_t>(), std::back_inserter(csvRows));

		for (const auto& strPerRow : csvRows)
		{
			std::vector<std::wstring> tokensPerRow;
			csvParser->datas.push_back({});
			
			auto& rowData = csvParser->datas[csvParser->datas.size() - 1];
			std::wistringstream rowSS(strPerRow);
			std::copy(split_istream_iterator<std::wstring, wchar_t>(rowSS, ','),
				split_istream_iterator<std::wstring, wchar_t>(), std::back_inserter(rowData));
		}


		return csvParser;
	}

}