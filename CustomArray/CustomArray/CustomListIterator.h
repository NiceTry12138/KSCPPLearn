#pragma once
#include "BaseIterator.h"
#include "CustomListNode.h"

template<typename T>
class CustomListIterator : public BaseIterator<T>
{
public:
	void next() override;
	void behind() override;
	bool isDone() override;

	CustomListIterator(CustomListNode<T>* _node, CustomListNode<T>* _head, bool reverse = false) : m_Node(_node), m_Head(_head), BaseIterator<T>(reverse) {}

	T operator *();
	CustomListIterator<T>& operator ++();
	CustomListIterator<T>& operator --();
	bool operator !=(const CustomListIterator<T>& _other);

	void SetVal(const T& _val) override;

private:
	CustomListNode<T>* m_Node;
	CustomListNode<T>* m_Head;

};

template<typename T>
inline void CustomListIterator<T>::next()
{
	m_Node = m_Node->next;
}

template<typename T>
inline void CustomListIterator<T>::behind()
{
	m_Node = m_Node->behind;
}

template<typename T>
inline bool CustomListIterator<T>::isDone()
{
	return m_Node == nullptr;
}

template<typename T>
inline T CustomListIterator<T>::operator*()
{
	return m_Node->_data;
}

template<typename T>
inline CustomListIterator<T>& CustomListIterator<T>::operator++()
{
	if (BaseIterator<T>::ISReverse())
	{
		behind();
	}
	else {
		next();
	}
	return *this;
}

template<typename T>
inline CustomListIterator<T>& CustomListIterator<T>::operator--()
{
	if (BaseIterator<T>::ISReverse())
	{
		next();
	}
	else {
		behind();
	}
	return *this;
}

template<typename T>
inline bool CustomListIterator<T>::operator!=(const CustomListIterator<T>& _other)
{
	return this->m_Node != _other.m_Node;
}

template<typename T>
inline void CustomListIterator<T>::SetVal(const T& _val)
{
	m_Node->_data = _val;
}