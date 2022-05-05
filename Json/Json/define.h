#pragma once
#include <string>
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

struct lept_member {
	std::string k;
	size_t klen; 
	lept_value v; 
};

struct lept_value {
	union {
		struct { lept_member* m; size_t size, capacity; }o; 
		struct { lept_value* e; size_t size, capacity; }a;
		struct { std::string s; size_t len; }s;
		double n;
	}u;
	lept_type type;
};
