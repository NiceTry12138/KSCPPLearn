#pragma once
#include "vector"
#include <iostream>

class CustomString
{
public:
	CustomString(const char* _str = nullptr);	// Ĭ�Ϲ���
	CustomString(const CustomString& _other);	// ��������
	CustomString& operator =(const CustomString& _other);

	inline bool operator == (const CustomString& _other);   
	
	friend std::ostream& operator<<(std::ostream& os, const CustomString& str) // ��Ԫ
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
	char* m_data{nullptr};						// ����ʵ�ʴ��λ��
};

