#include "leptjson.h"
#include <fstream>

LeptJsonClass::LeptJsonClass(std::string filepath)
{
}

LeptJsonClass::~LeptJsonClass()
{
}

lept_state LeptJsonClass::lept_parse_value(lept_context& c, lept_value& v)
{
	/*
		n -> null
		t -> true
		f -> false
		" -> string
		0-9/- -> number
		[ -> array
		{ -> object
	*/
	switch (c.json[c.currentIndex])
	{
	case 'n':
		return lept_parse_literal(c, v, "null", lept_type::LEPT_NULL);
	case 't':
		return lept_parse_literal(c, v, "true", lept_type::LEPT_TRUE);
	case 'f':
		return lept_parse_literal(c, v, "false", lept_type::LEPT_FALSE);
	case '"':
		return lept_parse_string(c, v);
	case '[':
		return lept_parse_array(c, v);
	case '{':
		return lept_parse_object(c, v);
	default:
		return lept_parse_number(c, v);
	}
	return lept_state::LEPT_PARSE_OK;
}

void LeptJsonClass::lept_context_whitespace(lept_context& c)
{
	while (c.getChar() == ' ' || c.getChar() == '\t' || c.getChar() == '\r' || c.getChar() == '\n')
	{
		++c.currentIndex;
	}
}

lept_state LeptJsonClass::lept_parse_number(lept_context& c, lept_value& v)
{
	std::string temp;
	if (c.getChar() == '-')
	{
		temp.push_back('-');
		++c.currentIndex;
	}
	if (c.getChar() == '0')
	{
		temp.push_back('0');
		++c.currentIndex;
		if (ISDIGITAL(c.getChar()))	// 如果第一位为0 而后面还有其他数字则是错误写法
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
	}
	else {
		if (!ISDIGITAL_1to9(c.getChar()))	// 如果符号位之后 既不是0 也不是1~9的数字，那么就是错误的写法
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;	
		}
		for (; ISDIGITAL(c.getChar()); ++c.currentIndex)
		{
			temp.push_back(c.getChar());
		}
	}
	if (c.getChar() == '.')
	{
		temp.push_back('.');
		++c.currentIndex;
		for (; ISDIGITAL(c.getChar()); ++c.currentIndex)
		{
			temp.push_back(c.getChar());
		}
	}

	v.u.number = strtod(temp.c_str(), NULL);
	v.type = lept_type::LEPT_NUMBER;
	return lept_state::LEPT_PARSE_OK;
}

lept_state LeptJsonClass::lept_parse_string(lept_context& c, lept_value& v)
{
	++c.currentIndex;
	std::string *temp = new std::string("\"");
	if (lept_parse_string_row(c, temp) == lept_state::LEPT_PARSE_OK)
	{
		temp->push_back('\"');
		v.u.str = temp;
		v.type = lept_type::LEPT_STRING;
		return lept_state::LEPT_PARSE_OK;
	}
	delete temp;
	return lept_state::LEPT_PARSE_INVALID_VALUE;
}

lept_state LeptJsonClass::lept_parse_array(lept_context& c, lept_value& v)
{
	++c.currentIndex;
	v.type = lept_type::LEPT_ARRAY;

	lept_context_whitespace(c);

	if (c.getChar() == ']')
	{
		lept_set_array_null(v);
		++c.currentIndex;
		return lept_state::LEPT_PARSE_OK;
	}

	std::vector<lept_value>* temp = new std::vector<lept_value>();
	while (true)
	{
		lept_value tempValue;
		if (lept_parse_value(c, tempValue) != lept_state::LEPT_PARSE_OK)
		{
			break;
		}
		temp->push_back(tempValue);
		lept_context_whitespace(c);
		if (c.getChar() == ',')
		{
			++c.currentIndex;
			lept_context_whitespace(c);
		}
		else if (c.getChar() == ']') {
			++c.currentIndex;
			v.u.arr = temp;
			return lept_state::LEPT_PARSE_OK;
		}
		else {
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
	}

	v.u.arr = temp;
	return lept_state::LEPT_PARSE_OK;
}

lept_state LeptJsonClass::lept_parse_object(lept_context& c, lept_value& v)
{
	++c.currentIndex;				// 跳过 "
	lept_context_whitespace(c);
	v.type = lept_type::LEPT_OBJECT;
	if (c.getChar() == '}')
	{
		++c.currentIndex;
		lept_set_object_null(v);
		return lept_state::LEPT_PARSE_OK;
	}
	lept_member* member = new lept_member();
	std::string* tempString = new std::string();
	while (true)
	{
		if (c.getChar() != '\"')
		{
			delete tempString;
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		if (lept_parse_string_row(c, tempString) != lept_state::LEPT_PARSE_OK)
		{
			delete tempString;
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		
		lept_context_whitespace(c);
		if (c.getChar() != ':')
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		++c.currentIndex;
		lept_context_whitespace(c);



		if (c.getChar() == ',')
		{
			++c.currentIndex;
			lept_context_whitespace(c);
		}
		else if (c.getChar() == '}')
		{
			++c.currentIndex;
			v.type = lept_type::LEPT_OBJECT;
			v.u.obj = member;
		}
		else {
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
	}

	return lept_state::LEPT_PARSE_OK;
}

lept_state LeptJsonClass::lept_parse_literal(lept_context& c, lept_value& v, const std::string typeString, lept_type type)
{
	bool isSameToTypeString = true;
	for (int i = 0; i < typeString.size(); ++i) {
		if (c.isOutofSize() || c.getChar() != typeString[i])
		{
			// 越界或者不相等 表示不合要求
			isSameToTypeString = false;
		}
		++c.currentIndex;
	}
	if (!isSameToTypeString)
	{
		return lept_state::LEPT_PARSE_INVALID_VALUE;
	}
	v.type = type;
	return lept_state::LEPT_PARSE_OK;
}

lept_state LeptJsonClass::lept_parse_string_row(lept_context& c, std::string* result)
{
	while (true)
	{
		switch (c.getChar())
		{
		case '\"':
			+c.currentIndex;
			return lept_state::LEPT_PARSE_OK;
			break;
		case '\\':
			++c.currentIndex;
			switch (c.getChar())
			{
			case '\"': result->push_back('\"'); break;
			case '\\': result->push_back('\\'); break;
			case '/':  result->push_back('/'); break;
			case 'b':  result->push_back('\b'); break;
			case 'f':  result->push_back('\f'); break;
			case 'n':  result->push_back('\n'); break;
			case 'r':  result->push_back('\r'); break;
			case 't':  result->push_back('\t'); break;
			default:
				return lept_state::LEPT_PARSE_INVALID_VALUE;// 转义字符后缺少东西 报错
				break;
			}
			++c.currentIndex;
			break;
		case '\0':
			return lept_state::LEPT_PARSE_INVALID_VALUE;	// 未读到"，却读到文件末尾，明显错误
			break;
		default:
			result->push_back(c.getChar());
			++c.currentIndex;
			break;
		}
	}
	return lept_state::LEPT_PARSE_INVALID_VALUE;
}

void LeptJsonClass::lept_set_array_null(lept_value& v)
{
	v.u.arr = nullptr;
	v.type = lept_type::LEPT_ARRAY;
}

void LeptJsonClass::lept_set_object_null(lept_value& v)
{
	v.u.obj = nullptr;
	v.type = lept_type::LEPT_OBJECT;
}
