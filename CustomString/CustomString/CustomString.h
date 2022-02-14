#pragma once
#include <vector>
#include <iostream>

class CustomString
{
public:
	/// <summary>
	/// KMPƥ���㷨 
	/// </summary>
	/// <param name="source">Ŀ�����ַ���</param>
	/// <param name="pattern">ģʽ��</param>
	/// <returns></returns>
	static int KMP(const char* source, const char* pattern, int findStartIndex = 0);

	/// <summary>
	/// KMP��Next���������㷨
	/// </summary>
	/// <param name="P">Ŀ���ַ���</param>
	/// <param name="next">Next���鷵��ֵ</param>
	static void CreateNext(const char* P, int* next);

	static void MoveNextArr(int* next, int length);
public:
	CustomString(const char* _str = nullptr);	// Ĭ�Ϲ���
	CustomString(const CustomString& _other);	// ��������
	CustomString& operator =(const CustomString& _other);

	void setData(const char* newData);

	inline bool operator == (const CustomString& _other) {
		return strcmp(m_data, _other.m_data) == 0;
	}
	inline bool operator != (const CustomString& _other) {
		return !((*this) == _other);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const CustomString& str) // ��Ԫ
	{
		os << str.m_data ;
		return os;
	}

	~CustomString();

	void append(const char* _other);
	void append(const CustomString& _other);
	
	int len();

	/// <summary>
	/// �и�� ���ҿ�[startIndex, endIndex]
	/// </summary>
	/// <param name="startIndex">��ʼ����</param>
	/// <param name="endIndex">��������</param>
	/// <returns>CustomString��m_data���и����ַ���</returns>
	CustomString sub(int startIndex = 0, int endIndex = -1);

	std::vector<CustomString> split(const char* _key);

	int find(const char* _target);
	int find(const CustomString &_target);
protected:
	void setValueByOtherCustomString(const char* _other);
	
private:
	char* m_data{nullptr};						// ����ʵ�ʴ��λ��
};

