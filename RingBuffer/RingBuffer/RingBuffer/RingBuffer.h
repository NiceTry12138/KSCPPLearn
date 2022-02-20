#pragma once


class RingBuffer
{
public:
	RingBuffer(int size);
	~RingBuffer();

	bool pop(char* val);
	void push(const char* val);

	int size();
protected:
	void resize(int length);
	void autoResize(int hopeLength);
	inline bool isEmpty();
	inline bool isFull();
	inline void deleteData(char** _data, int length);

	void shallowCopy(char** &target,char** &origin, int length, int dataFront, int dataRear, int dataLength);

	void testlog();
private:
	int m_front{ 0 };
	int m_rear{ 0 };
	int m_currentSize{ 0 };
	int m_realSize{ 0 };
	char** m_data{ nullptr };
};

