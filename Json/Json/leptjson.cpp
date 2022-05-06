#include "leptjson.h"
#include <fstream>
#include <sstream>
using namespace std;

LeptJsonClass::LeptJsonClass(std::string filepath)
{
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();

	LeptJson::lept_context c;

	c.json = std::string(buffer.str());
	LeptJsonClass::lept_parse_object(c, m_root);
}

LeptJsonClass::~LeptJsonClass()
{
	deleteAll(m_root);
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
		if (ISDIGITAL(c.getChar()))	// �����һλΪ0 �����滹�������������Ǵ���д��
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
	}
	else {
		if (!ISDIGITAL_1to9(c.getChar()))	// �������λ֮�� �Ȳ���0 Ҳ����1~9�����֣���ô���Ǵ����д��
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
	++c.currentIndex;				// ���� {
	lept_context_whitespace(c);
	v.type = lept_type::LEPT_OBJECT;
	if (c.getChar() == '}')
	{
		++c.currentIndex;
		lept_set_object_null(v);
		return lept_state::LEPT_PARSE_OK;
	}
	v.u.obj = new std::vector<lept_member>();
	while (true)
	{
		std::string tempString;
		if (c.getChar() != '\"')
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		++c.currentIndex;			// ���� ��
		if (lept_parse_string_row(c, &tempString) != lept_state::LEPT_PARSE_OK)
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		
		lept_context_whitespace(c);
		if (c.getChar() != ':')
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}
		++c.currentIndex;
		lept_context_whitespace(c);

		lept_member member;
		member.key = std::string(tempString);
		

		if (lept_parse_value(c, member.v) != lept_state::LEPT_PARSE_OK)
		{
			return lept_state::LEPT_PARSE_INVALID_VALUE;
		}

		lept_context_whitespace(c);
		if (c.getChar() == ',')
		{
			++c.currentIndex;
			v.u.obj->push_back(member);
			lept_context_whitespace(c);
		}
		else if (c.getChar() == '}')
		{
			++c.currentIndex;
			v.type = lept_type::LEPT_OBJECT;
			v.u.obj->push_back(member);
			return lept_state::LEPT_PARSE_OK;
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
			// Խ����߲���� ��ʾ����Ҫ��
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
			++c.currentIndex;
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
				return lept_state::LEPT_PARSE_INVALID_VALUE;// ת���ַ���ȱ�ٶ��� ����
				break;
			}
			++c.currentIndex;
			break;
		case '\0':
			return lept_state::LEPT_PARSE_INVALID_VALUE;	// δ����"��ȴ�����ļ�ĩβ�����Դ���
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

void LeptJsonClass::deleteAll(lept_value& _item)
{
	switch (_item.type)
	{		
	case lept_type::LEPT_STRING:
		delete _item.u.str;
		break;
	case lept_type::LEPT_ARRAY:
		if (_item.u.arr == nullptr)
		{
			break;
		}
		for (int i = 0; i < _item.u.arr->size(); ++i) {
			deleteAll(_item.u.arr->at(i));
		}
		delete _item.u.arr;
		break;
	case lept_type::LEPT_OBJECT:
		if (_item.u.obj == nullptr)
		{
			break;
		}
		for (int i = 0; i < _item.u.obj->size(); ++i) {
			deleteAll(_item.u.obj->at(i));
		}
		delete _item.u.obj;
		break;
	default:
		break;
	}
}

void LeptJsonClass::deleteAll(lept_member& _item)
{
	switch (_item.v.type)
	{
	case lept_type::LEPT_STRING:
		delete _item.v.u.str;
		break;
	case lept_type::LEPT_ARRAY:
		if (_item.v.u.arr == nullptr)
		{
			break;
		}
		for (int i = 0; i < _item.v.u.arr->size(); ++i) {
			deleteAll(_item.v.u.arr->at(i));
		}
		delete _item.v.u.arr;
		break;
	case lept_type::LEPT_OBJECT:
		if (_item.v.u.obj == nullptr)
		{
			break;
		}
		for (int i = 0; i < _item.v.u.obj->size(); ++i) {
			deleteAll(_item.v.u.obj->at(i));
		}
		delete _item.v.u.obj;
		break;
	default:
		break;
	}
}
