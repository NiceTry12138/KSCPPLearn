#pragma once
#include <string.h>
template<typename ElementType, int ElementCount>
class FStackArray
{
public:
	FStackArray();
	~FStackArray();

	void pushBackElement(const ElementType& val);
	ElementType popBackElement();
	ElementType getElementByIndex(int index);

	size_t getLength();

protected:
	void resize(size_t size);

private:
	size_t m_ElementNumber{ 0 };
	size_t m_CurrentArraySize{ 0 };

	ElementType* m_startPtr{ nullptr };
};

template<typename ElementType, int ElementCount>
inline FStackArray<ElementType, ElementCount>::FStackArray()
{
	m_startPtr = static_cast<ElementType*>(alloca(sizeof(ElementType) * ElementCount));
	m_ElementNumber = 0;
	m_CurrentArraySize = ElementCount; 
}

template<typename ElementType, int ElementCount>
inline FStackArray<ElementType, ElementCount>::~FStackArray()
{
}

template<typename ElementType, int ElementCount>
inline void FStackArray<ElementType, ElementCount>::pushBackElement(const ElementType& val)
{
	if (m_ElementNumber >= m_CurrentArraySize)
	{
		return;
	}
	m_startPtr[m_ElementNumber] = val;
	++m_ElementNumber;
}

template<typename ElementType, int ElementCount>
inline ElementType FStackArray<ElementType, ElementCount>::popBackElement()
{
	if (m_ElementNumber == 0)
	{
		return NULL;
	}
	--m_ElementNumber;
	return m_startPtr[m_ElementNumber];
}

template<typename ElementType, int ElementCount>
inline ElementType FStackArray<ElementType, ElementCount>::getElementByIndex(int index)
{
	if (index >= m_ElementNumber)
	{
		return NULL;
	}
	return m_startPtr[index];
}

template<typename ElementType, int ElementCount>
inline size_t FStackArray<ElementType, ElementCount>::getLength()
{
	return m_ElementNumber;
}

template<typename ElementType, int ElementCount>
inline void FStackArray<ElementType, ElementCount>::resize(size_t size)
{
	if (size <= m_CurrentArraySize)
	{
		return;
	}
	auto newPtr = alloca(sizeof(ElementType) * size);
	memcpy(newPtr, m_startPtr, sizeof(ElementType) * m_CurrentArraySize);
}
