#include "CustomString.h"
#include <string.h>

int CustomString::KMP(const char* source, const char* pattern, int findStartIndex) {
	int result = -1;
	int sourceLen = strlen(source);
	int patternLen = strlen(pattern);

	int* patternNext = new int[patternLen];

	CreateNext(pattern, patternNext);

	// source 使用 sIndex 定位
	// pattern 使用 pIndex 定位
	int sIndex = findStartIndex, pIndex = 0;
	while (sIndex < sourceLen)
	{
		if (pIndex == patternLen - 1 && pattern[pIndex] == source[sIndex])	// 表示找到 返回序号
		{
			result = sIndex - patternLen + 1;								// 手动算一下就知道为什么+1  从0开始的序号，当前在第4位找到，模式串长度为2,4-2+1才是开始位置
			break;
		}
		if (source[sIndex] == pattern[pIndex]) {
			++sIndex, ++pIndex;
		}
		else {
			pIndex = patternNext[pIndex];
			if (pIndex == -1)												// 表示从最开始就不匹配，所以直接跳过
			{
				++pIndex, ++sIndex;
			}
		}
	}

	delete[] patternNext;
	return result;
}

void CustomString::CreateNext(const char* P, int* next)
{
	int q, k;							//q:模版字符串下标；k:最大前后缀长度
	int m = strlen(P);					//模版字符串长度
	memset(next, 0, m);
	next[0] = 0;						//模版字符串的第一个字符的最大前后缀长度为0
	for (q = 1, k = 0; q < m; ++q)		//for循环，从第二个字符开始，依次计算每一个字符对应的next值
	{
		while (k > 0 && P[q] != P[k])	//递归的求出P[0]···P[q]的最大的相同的前后缀长度k
		{
			k = next[k - 1];			//不理解没关系看下面的分析，这个while循环是整段代码的精髓所在，确实不好理解  
		}
		if (P[q] == P[k])				//如果相等，那么最大相同前后缀长度加1
		{
			k++;
		}
		next[q] = k;
	}
	MoveNextArr(next, strlen(P));		// 为了方便KMP算法将数组往后移动一个位，并将第一位补齐为-1
}

void CustomString::MoveNextArr(int* next, int length)
{
	for (int i = length - 1; i > 0; --i) {
		next[i] = next[i - 1];
	}
	next[0] = -1;
}

CustomString::CustomString(const char* _str)
{
	if (_str) {
		setValueByOtherCustomString(_str);
		//m_data = new char[strlen(_str) + 1];
		//strcpy(m_data, _str);
	}
	else {
		setValueByOtherCustomString("\0");
		//m_data = new char[1];
		//*m_data = '\0';
	}
}

CustomString::CustomString(const CustomString& _other)
{
	setValueByOtherCustomString(_other.m_data);
}

CustomString& CustomString::operator=(const CustomString& _other)
{
	// 防止自己给自己赋值的情况
	if (this == &_other) {
		return *this;
	}
	setValueByOtherCustomString(_other.m_data);
	return *this;
}

void CustomString::setData(const char* newData)
{
	setValueByOtherCustomString(newData);
}

//inline bool CustomString::operator==(const CustomString& _other)
//{
//	return strcmp(m_data, _other.m_data) == 0;
//}
//
//inline bool CustomString::operator!=(const CustomString& _other)
//{
//	return !((*this) == _other);
//}

CustomString::~CustomString()
{
	delete[] m_data;
}

void CustomString::append(const char* _other)
{
	int targetLen = strlen(m_data) + strlen(_other) + 1;
	char* newData = new char[targetLen];
	memset(newData, '\0', targetLen);
	strcpy(newData, m_data);
	strcat(newData, _other);
	delete[] m_data;
	m_data = newData;
}

void CustomString::append(const CustomString& _other)
{
	append(_other.m_data);
}

int CustomString::len()
{
	if (m_data == nullptr)
	{
		return 0;
	}
	return strlen(m_data);
}

CustomString CustomString::sub(int startIndex, int endIndex)
{
	if (endIndex >= len())
	{
		std::cout << "			endIndex rather than this String length" << std::endl;
		return CustomString();
	}
	if (startIndex < 0 || startIndex >= len())
	{
		std::cout << "			startIndex less than 0 or rather than this String Length" << std::endl;
		return CustomString();
	}
	if (startIndex > endIndex) {
		std::cout << "			startIndex rather than endIndex" << std::endl;
		return CustomString();
	}
	int targetLen = endIndex - startIndex + 1;
	char* newStr = new char[targetLen + 1];
	memset(newStr, '\0', targetLen + 1);
	memcpy(newStr, m_data + sizeof(char) * startIndex, sizeof(char) * targetLen);
	auto result = CustomString(newStr);
	delete[] newStr;
	return result;
}

std::vector<CustomString> CustomString::split(const char* _key)
{
	int keyLen = strlen(_key);
	std::vector<CustomString> result;
	
	int findIndex = 0;
	int lastIndex = 0;
	while (findIndex != -1)
	{
		findIndex = KMP(m_data, _key, lastIndex);
		if (findIndex == -1)
		{
			result.push_back(CustomString(sub(lastIndex, len() - 1)));
			break;
		}
		else {
			result.push_back(CustomString(sub(lastIndex, findIndex - 1)));
		}
		
		lastIndex = findIndex + keyLen;
	}
	return result;
}

int CustomString::find(const char* _target)
{
	int result = -1;
	if (strlen(_target) == 0) {
		return 0;
	}

	if (strlen(this->m_data) < strlen(_target)) {
		return -1;
	}

	if (strlen(this->m_data) == strlen(_target)) {
		return strcmp(this->m_data, _target) == 0;
	}

	return KMP(this->m_data, _target);
}

int CustomString::find(const CustomString& _target)
{
	return find(_target.m_data);
}

void CustomString::setValueByOtherCustomString(const char* _other)
{
	delete[] m_data;
	m_data = new char[strlen(_other) + 1];
	m_data[strlen(_other)] = '\0';
	strcpy(m_data, _other);
}