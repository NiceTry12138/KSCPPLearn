#pragma once
#include <string>
#include <vector>

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
			lept_member* obj;				// object
			std::vector<lept_value>* arr;	// array
			std::string* str;				// string
			double number;					// number
		}u;
		lept_type type;
		lept_value() {
			u.obj = nullptr;
			type = lept_type::LEPT_NULL;
		}
		~lept_value() {
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
}