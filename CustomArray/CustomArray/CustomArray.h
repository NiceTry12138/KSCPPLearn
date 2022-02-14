#pragma once
#include <iostream>
#include <assert.h>
#include <iosfwd>
#include <string.h>
using namespace std;

template<typename T>
class CustomArray
{
public:

public:
	CustomArray() {

	}
	~CustomArray() {
		delete[] m_data;
	}
	CustomArray(std::initializer_list<T> initlist) {
		m_data = new T[initlist.size()];
		int index = 0;
		for (auto val : initlist) {
			m_data[index++] = val;
		}
		m_length = initlist.size();
		m_realLength = m_length;
	}

	void reserve(int len) {
		resize(len);
	}

	void push(const T val) {
		autoResize(m_length + 1);
		m_data[m_length + 1] = val;
		m_length++;
	}
	T pop() {
		m_length--;
		return m_data[m_length + 1];
	}

	void insert(int index, T val) {
		if (index == m_length) {
			push(val);
			return;
		}
		isOutOfRange(index);
		autoResize(m_length + 1);
		for (int i = m_length; i > index; i--) {
			m_data[m_length] = m_data[m_length - 1];
		}
		m_data[index] = val;
	}

	T remove(int index) {
		isOutOfRange(index);
		T result = m_data[index];
		for (int i = 0; i < m_length - 1; ++i) {
			if (i < index) {
				continue;
			}
			m_data[i] = m_data[i + 1];
		}
		--m_length;
		return result;
	}

	void clear() {
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
		m_realLength = 0;
	}

	int findIndex(T val) {
		for (int i = 0; i < m_length; i++) {
			if (m_data[i] == val) {
				return i;
			}
		}
		return -1;
	}

	int size() {
		return m_length;
	}

	T at(int index) {
		isOutOfRange(index);
		return m_data[index];
	}

protected:
	void isOutOfRange(int index) {
		if (index >= m_length || index < 0)
		{
			assert(false);
		}
	}

	void autoResize(int targetLen) {
		// 如果实际内容大于期望内容 不做处理
		if (m_realLength > targetLen)
		{
			return;
		}
		static int g_lengthList[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216 };
		int realLen = 0;
		for (int i = 0; i < 25; ++i) {
			if (g_lengthList[i] > targetLen) {
				realLen = g_lengthList[i];
				break;
			}
		}
		resize(realLen);
	}

	void resize(int targetLen) {
		// 小了就不做处理
		if (targetLen <= m_length) {
			return;
		}
		T* newData = new T[targetLen];
		int len = sizeof(newData);
		memset(newData, 0, targetLen * sizeof(T));
		memcpy(newData, m_data, m_length * sizeof(T));
		m_realLength = targetLen;
		delete[] m_data;
		m_data = newData;
		newData = nullptr;
	}

private:
	int tag{ -1 };

	int m_realLength{ 0 };
	int m_length{ 0 };
	T* m_data{ nullptr };
};

