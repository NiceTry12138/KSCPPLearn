#pragma once
#include <vector>
#include <iostream>

class CustomString
{
public:
	/// <summary>
	/// KMP匹配算法 
	/// </summary>
	/// <param name="source">目标主字符串</param>
	/// <param name="pattern">模式串</param>
	/// <returns></returns>
	static int KMP(const char* source, const char* pattern, int findStartIndex = 0);

	/// <summary>
	/// KMP的Next数组生成算法
	/// </summary>
	/// <param name="P">目标字符串</param>
	/// <param name="next">Next数组返回值</param>
	static void CreateNext(const char* P, int* next);

	static void MoveNextArr(int* next, int length);
public:
	CustomString(const char* _str = nullptr);	// 默认构造
	CustomString(const CustomString& _other);	// 拷贝构造
	CustomString& operator =(const CustomString& _other);

	void setData(const char* newData);

	inline bool operator == (const CustomString& _other) {
		return strcmp(m_data, _other.m_data) == 0;
	}
	inline bool operator != (const CustomString& _other) {
		return !((*this) == _other);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const CustomString& str) // 友元
	{
		os << str.m_data ;
		return os;
	}

	~CustomString();

	void append(const char* _other);
	void append(const CustomString& _other);
	
	int len();

	/// <summary>
	/// 切割函数 左开右开[startIndex, endIndex]
	/// </summary>
	/// <param name="startIndex">起始坐标</param>
	/// <param name="endIndex">结束坐标</param>
	/// <returns>CustomString的m_data存切割后的字符串</returns>
	CustomString sub(int startIndex = 0, int endIndex = -1);

	std::vector<CustomString> split(const char* _key);

	int find(const char* _target);
	int find(const CustomString &_target);
protected:
	void setValueByOtherCustomString(const char* _other);
	
private:
	char* m_data{nullptr};						// 数据实际存放位置
};

