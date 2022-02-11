#pragma once
#include "vector"
#include <iostream>

class CustomString
{
public:
	CustomString(const char* _str = nullptr);	// 默认构造
	CustomString(const CustomString& _other);	// 拷贝构造
	CustomString& operator =(const CustomString& _other);

	inline bool operator == (const CustomString& _other);   
	
	friend std::ostream& operator<<(std::ostream& os, const CustomString& str) // 友元
	{
		os << str.m_data ;
		return os;
	}

	~CustomString();

	void append(const char* _other);
	void append(const CustomString& _other);
	
	int len();

	CustomString sub(int startIndex = 0, int endIndex = -1);

	std::vector<CustomString> split(const char* _key);
protected:
	void setValueByOtherCustomString(const char* _other);
	
private:
	char* m_data{nullptr};						// 数据实际存放位置
};

