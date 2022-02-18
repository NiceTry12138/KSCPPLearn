#include "RingBuffer.h"

RingBuffer::RingBuffer(uint size)
{
}

RingBuffer::~RingBuffer()
{
	delete[] m_data;
}
