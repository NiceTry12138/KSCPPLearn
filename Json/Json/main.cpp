#include <iostream>
#include "define.h"
#include "leptjson.h"
#include <fstream>
#include <sstream>
using namespace std;

void testprint(const LeptJson::lept_value& v) {
	switch (v.type)
	{
	case lept_type::LEPT_NULL:
		std::cout << "null" << std::endl;
		break;
	case lept_type::LEPT_FALSE:
		std::cout << "false" << std::endl;
		break;
	case lept_type::LEPT_TRUE:
		std::cout << "true" << std::endl;
		break;
	case lept_type::LEPT_NUMBER:
		std::cout << v.u.number << std::endl;
		break;
	case lept_type::LEPT_STRING:
		std::cout << v.u.str->c_str() << std::endl;
		break;
	case lept_type::LEPT_ARRAY:
		for (int i = 0; i < v.u.arr->size(); ++i)
		{
			testprint(v.u.arr->at(i));
		}
		break;
	case lept_type::LEPT_OBJECT:
		for (int i = 0; i < v.u.obj->size(); ++i)
		{
			std::cout << v.u.obj->at(i).key << " : ";
			testprint(v.u.obj->at(i).v);
		}
		break;
	default:
		break;
	}
}

void testJson() {

	LeptJson::lept_context c;
	std::string temp;
	LeptJson::lept_value v;
	//c.json = "true";
	//LeptJsonClass::lept_parse_literal(c, v, "true", lept_type::LEPT_TRUE);
	//c.json = "false";
	//LeptJsonClass::lept_parse_literal(c, v, "false", lept_type::LEPT_FALSE);
	//c.json = "null";
	//LeptJsonClass::lept_parse_literal(c, v, "null", lept_type::LEPT_NULL);
	//c.json = "-0.1234";
	//LeptJsonClass::lept_parse_number(c, v) != lept_state::LEPT_PARSE_OK;
	//c.json = "\"qw\\n\"";
	//LeptJsonClass::lept_parse_string(c, v) != lept_state::LEPT_PARSE_OK;
	//c.json = "[[11, 22, 33], [\"1\", \"1\", \"1\"], [null, false, true], [1], []]";
	//LeptJsonClass::lept_parse_array(c, v) != lept_state::LEPT_PARSE_OK;

	//std::ifstream t("test.txt");
	//std::stringstream buffer;
	//buffer << t.rdbuf();

	//c.json = std::string(buffer.str());
	//LeptJsonClass::lept_parse_object(c, v);

	//testprint(v);
}

int main() {
	//testJson();
	
	LeptJsonClass js("test.txt");
	testprint(js.m_root);

	return 0;
}