#include "CustomString.h"
#include <string.h>

static int KMP(const char* source, const char* pattern) {

	return -1;
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
	// TODO: 在此处插入 return 语句
}

inline bool CustomString::operator==(const CustomString& _other)
{
	return strcmp(m_data, _other.m_data) == 0;
}

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
		std::cout << "endIndex rather than this String length";
		return nullptr;
	}
	if (startIndex < 0 || startIndex >= len())
	{
		std::cout << "startIndex less than 0 or rather than this String Length";
		return nullptr;
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
	return std::vector<CustomString>();
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

	return result;
}

void CustomString::setValueByOtherCustomString(const char* _other)
{
	delete[] m_data;
	m_data = new char[strlen(_other) + 1];
	m_data[strlen(_other)] = '\0';
	strcpy(m_data, _other);
}