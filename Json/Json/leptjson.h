#pragma once
#include <string>
#include "define.h"

using namespace LeptJson;

class LeptJsonClass
{
public:
//protected:
	static lept_state lept_parse_value(lept_context& c, lept_value& v);		// ����ֵ
	static void lept_context_whitespace(lept_context& c);					// ����հ��ַ�
	static lept_state lept_parse_number(lept_context& c, lept_value& v);	// ��������
	static lept_state lept_parse_string(lept_context& c, lept_value& v);	// �����ַ���
	static lept_state lept_parse_array(lept_context& c, lept_value& v);		// ��������
	static lept_state lept_parse_object(lept_context& c, lept_value& v);	// ��������
	static lept_state lept_parse_literal(lept_context& c, lept_value& v, const std::string typeString, lept_type type);	// ���� null, false, true�������

	static lept_state lept_parse_string_row(lept_context& c, std::string* result);

	static void lept_set_array_null(lept_value& v);
	static void lept_set_object_null(lept_value& v);


public:
	LeptJsonClass(std::string filepath);
	~LeptJsonClass();

protected:
	void deleteAll(lept_value& _item);
	void deleteAll(lept_member& _item);

private:
public:
	lept_context m_jsoncontext;
	lept_value m_root;
};