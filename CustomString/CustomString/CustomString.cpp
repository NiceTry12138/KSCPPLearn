#include "CustomString.h"
#include <string.h>

int CustomString::KMP(const char* source, const char* pattern, int findStartIndex) {
	int result = -1;
	int sourceLen = strlen(source);
	int patternLen = strlen(pattern);

	int* patternNext = new int[patternLen];

	CreateNext(pattern, patternNext);

	// source ʹ�� sIndex ��λ
	// pattern ʹ�� pIndex ��λ
	int sIndex = findStartIndex, pIndex = 0;
	while (sIndex < sourceLen)
	{
		if (pIndex == patternLen - 1 && pattern[pIndex] == source[sIndex])	// ��ʾ�ҵ� �������
		{
			result = sIndex - patternLen + 1;								// �ֶ���һ�¾�֪��Ϊʲô+1  ��0��ʼ����ţ���ǰ�ڵ�4λ�ҵ���ģʽ������Ϊ2,4-2+1���ǿ�ʼλ��
			break;
		}
		if (source[sIndex] == pattern[pIndex]) {
			++sIndex, ++pIndex;
		}
		else {
			pIndex = patternNext[pIndex];
			if (pIndex == -1)												// ��ʾ���ʼ�Ͳ�ƥ�䣬����ֱ������
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
	int q, k;							//q:ģ���ַ����±ꣻk:���ǰ��׺����
	int m = strlen(P);					//ģ���ַ�������
	memset(next, 0, m);
	next[0] = 0;						//ģ���ַ����ĵ�һ���ַ������ǰ��׺����Ϊ0
	for (q = 1, k = 0; q < m; ++q)		//forѭ�����ӵڶ����ַ���ʼ�����μ���ÿһ���ַ���Ӧ��nextֵ
	{
		while (k > 0 && P[q] != P[k])	//�ݹ�����P[0]������P[q]��������ͬ��ǰ��׺����k
		{
			k = next[k - 1];			//�����û��ϵ������ķ��������whileѭ�������δ���ľ������ڣ�ȷʵ�������  
		}
		if (P[q] == P[k])				//�����ȣ���ô�����ͬǰ��׺���ȼ�1
		{
			k++;
		}
		next[q] = k;
	}
	MoveNextArr(next, strlen(P));		// Ϊ�˷���KMP�㷨�����������ƶ�һ��λ��������һλ����Ϊ-1
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
	// ��ֹ�Լ����Լ���ֵ�����
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