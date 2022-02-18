#pragma once

typedef unsigned int uint;

class RingBuffer
{
public:
	RingBuffer(uint size);
	~RingBuffer();



protected:


private:
	int m_front{ 0 };
	int m_rear{ 0 };
	int m_currentSize{ 0 };
	char** m_data{ nullptr };
};

