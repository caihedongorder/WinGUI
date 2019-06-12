#pragma once
#include <Core.h>
#include <xutility>
#include <string>
#include <vector>

namespace Core
{
	template<class _Ty,
		class _Elem = char,
		class _Traits = std::char_traits<_Elem>,
		class _Diff = std::ptrdiff_t>
		class split_istream_iterator
		: public std::iterator<std::input_iterator_tag, _Ty, _Diff,
		const _Ty *, const _Ty&>
	{	// wrap _Ty extracts from input stream as input iterator
		typedef split_istream_iterator<_Ty, _Elem, _Traits, _Diff> _Myt;
	public:
		typedef _Elem char_type;
		typedef _Traits traits_type;
		typedef std::basic_istream<_Elem, _Traits> istream_type;

		typedef const _Ty *pointer;

		constexpr split_istream_iterator()
			: _Myistr(0), _Myval(),_delimiter(',')
		{	// construct singular iterator
		}

		split_istream_iterator(istream_type& _Istr, _Elem InDelimiter)
			: _Myistr(&_Istr)
			, _delimiter(InDelimiter)
		{	// construct with input stream
			_Getval();
		}

		const _Ty& operator*() const
		{	// return designated value
			return (_Myval);
		}

		pointer operator->() const
		{	// return pointer to class object
			return (std::pointer_traits<pointer>::pointer_to(**this));
		}

		_Myt& operator++()
		{	// preincrement
			_Getval();
			return (*this);
		}

		_Myt operator++(int)
		{	// postincrement
			_Myt _Tmp = *this;
			++*this;
			return (_Tmp);
		}

		bool _Equal(const _Myt& _Right) const
		{	// test for iterator equality
			return (_Myistr == _Right._Myistr);
		}

		friend bool operator != (const _Myt& InLhs, const _Myt& InRhs) noexcept {
			return !InLhs._Equal(InRhs);
		}
		friend bool operator == (const _Myt& InLhs, const _Myt& InRhs) noexcept {
			return InLhs._Equal(InRhs);
		}

	protected:
		void _Getval()
		{	// get a _Ty value if possible
			_Myval.clear();
			_Ty::value_type data;
			if (!_Myistr->eof())
			{
				_Myistr->get(data);

				auto bQuote = false;
				_Ty::value_type quote;
				if (data == '\"') { bQuote = true; quote = '\"'; }
				if (data == '\'') { bQuote = true; quote = '\''; }

				if (bQuote)
				{
					_Myval.push_back(data);
					_Myistr->get(data);
				}
				do 
				{
					if (bQuote)
					{
						_Myval.push_back(data);
						if (data == quote)
						{
							_Myistr->get(data);
							break;
						}
					}
					else
					{
						if (data == _delimiter || data == '\r' || data == '\n')
						{
							if (data == '\r') _Myistr->get(data);
							break;
						}
						_Myval.push_back(data);
					}
					_Myistr->get(data);
				} while (!_Myistr->eof());
			}
			else
			{
				_Myistr = 0;
			}
		}

		_Elem _delimiter;
		istream_type *_Myistr;	// pointer to input stream
		_Ty _Myval;	// lookahead value (valid if _Myistr is not null)
	};	

	class StringUtil
	{
	public:

		static bool StartWith(const std::string& InStr, const std::string& InSubStr) {
			if (InSubStr.size() > InStr.size())
			{
				return false;
			}
			auto numSubStr = InSubStr.size();
			for (auto iStr = 0 ; iStr < numSubStr; ++iStr)
			{
				if (InStr[iStr] != InSubStr[iStr])
					return false;
			}
			return true;
		}

		static bool EndWith(const std::string& InStr, const std::string& InSubStr) {
			if (InSubStr.size() > InStr.size())
			{
				return false;
			}
			auto StrIdx = InStr.size() - 1;
			auto numSubStr = InSubStr.size();
			for (auto iStr = 0; iStr < numSubStr; ++iStr)
			{
				if (InStr[StrIdx--] != InSubStr[numSubStr - 1 - iStr])
					return false;
			}
			return true;
		}
	};
}
