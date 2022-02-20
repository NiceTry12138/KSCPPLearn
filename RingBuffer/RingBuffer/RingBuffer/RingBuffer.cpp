#include "RingBuffer.h"
#include "string.h"
#include <iostream>

RingBuffer::RingBuffer(int size){
	m_data = new char*[size];
	for (int i = 0; i < size; i++) {
		m_data[i] = nullptr;
	}
	m_realSize = size;
}

RingBuffer::~RingBuffer()
{
	deleteData(m_data, m_realSize);
}

bool RingBuffer::pop(char* val)
{
	if (m_rear == m_front)
	{
		return false;
	}
	strcpy(val, m_data[m_front]);
	delete[] m_data[m_front];
	m_data[m_front] = nullptr;
	m_front++;

	--m_currentSize;
	autoResize(m_currentSize);

	return true;
}

void RingBuffer::push(const char* val)
{
	autoResize(m_currentSize + 1);

	int targetSize = strlen(val);
	char* target = new char[targetSize + 1];
	strcpy(target, val);
	target[targetSize] = '\0';
	m_data[m_rear] = target;
	++m_rear;
	m_rear %= m_realSize;

	++m_currentSize;
	//testlog();
}

int RingBuffer::size()
{
	return m_currentSize;
}

void RingBuffer::resize(int length)
{
	if (m_currentSize >= length)
	{
		return;
	}

	char** newData = nullptr;
	shallowCopy(newData, m_data, length, m_front, m_rear, m_realSize);
	delete[] m_data;
	m_data = nullptr;
	m_data = newData;
	m_realSize = length;
	m_front = 0;
	m_rear = m_currentSize;

	if (m_data[0] == NULL)
	{
		int xxxx = 0;
	}
}

void RingBuffer::autoResize(int hopeLength)
{
	if (hopeLength >= m_realSize)
	{
		resize(m_realSize * 2);
	}
	else if (m_realSize / 2 > hopeLength) {
		resize(m_realSize / 2);
	}
}

inline bool RingBuffer::isEmpty()
{
	return m_front == m_rear;
}

inline bool RingBuffer::isFull()
{
	return (m_front + 1) % m_currentSize == m_rear;
}

inline void RingBuffer::deleteData(char** _data, int length)
{
	for (int i = 0; i < length; i++) {
		delete[] _data[i];
	}
	delete[] _data;
	_data = nullptr;
}

void RingBuffer::shallowCopy(char** &target,char** &origin, int length, int dataFront, int dataRear, int dataLength)
{
	target = new char* [length];
	for (int i = 0; i < length; i++) {
		target[i] = nullptr;
	}
	int index = 0;
	while (dataFront != dataRear)
	{
		target[index] = origin[dataFront];
		++index;
		++dataFront;
		dataFront %= dataLength;
	}
}

void RingBuffer::testlog()
{
	for (int i = 0; i < m_realSize; ++i) {
		if (m_data[i] == nullptr)
		{
			std::cout << "null ";
		}
		else {
			std::cout << "vald ";
		}
	}
	std::cout << std::endl;
}
