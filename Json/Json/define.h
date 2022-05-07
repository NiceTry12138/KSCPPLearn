#pragma once
#include <string>
#include <vector>
#include <assert.h>

namespace LeptJson {

#define ISDIGITAL(ch) ((ch) >= '0' && ch <= '9')
#define ISDIGITAL_1to9(ch) ((ch) >= '1' && ch <= '9')

	struct lept_member;

	enum class lept_type
	{
		LEPT_NULL,
		LEPT_FALSE,
		LEPT_TRUE,
		LEPT_NUMBER,
		LEPT_STRING,
		LEPT_ARRAY,
		LEPT_OBJECT
	};	// Json的几种数据类型

	enum class lept_state {
		LEPT_PARSE_OK = 0,
		LEPT_PARSE_EXPECT_VALUE,
		LEPT_PARSE_INVALID_VALUE,
		LEPT_PARSE_ROOT_NOT_SINGULAR
	};	// 解析结果

	struct lept_value {
		union data {
			std::vector<lept_member>* obj;				// object
			std::vector<lept_value>* arr;	// array
			std::string* str;				// string
			double number;					// number
		}u;
		lept_type type;
		lept_value() {
			u.obj = nullptr;
			u.arr = nullptr;
			u.str = nullptr;
			type = lept_type::LEPT_NULL;
		}
		~lept_value() {
		}
		bool GetBool() {
			assert(type != lept_type::LEPT_NULL);
			if (type == lept_type::LEPT_FALSE)
			{
				return false;
			}
			else if (type == lept_type::LEPT_TRUE)
			{
				return true;
			}
			assert(0);
			return false;
		}
		std::string GetString() {
			assert(type != lept_type::LEPT_STRING);
			assert(u.str != nullptr);
			return std::string(u.str->c_str());
		}
		double GetNumber() {
			assert(type != lept_type::LEPT_NUMBER);
			return u.number;
		}
		lept_value GetItemByArrayIndex(int index) {
			assert(type != lept_type::LEPT_ARRAY);
			assert(u.arr != nullptr);
			assert(u.arr->size() > index);
			return u.arr->at(index);
		}
	};

	struct lept_member {
		std::string key;
		lept_value v;
	};

	struct lept_context {
		std::string json;
		int currentIndex{ 0 };
		char getChar() {
			char temp = json[currentIndex];
			return json[currentIndex];
		}
		bool isOutofSize() {
			return currentIndex >= json.size();
		}
	};

	static lept_value GetLeptValueObjectByKey(const lept_value& v, const std::string& key) {
		assert(v.type != lept_type::LEPT_OBJECT);
		assert(v.u.obj != nullptr);
		for (int i = 0; i < v.u.obj->size(); ++i) {
			if (v.u.obj->at(i).key == key)
			{
				return v.u.obj->at(i).v;
			}
		}
		return lept_value();
	}
}