#pragma once

#include "CustomListNode.h"
#include "CustomListIterator.h"
#include <assert.h>

template<typename T>
class CustomList
{
public:
	CustomList();
	virtual ~CustomList();

	CustomListNode<T>* push(const T& _val);
	T pop();

	CustomListNode<T>* insert(CustomListNode<T>* node, T val);
	int find(T val);
	void remove(CustomListNode<T>* node);
	void popAll();

	size_t Size();

	CustomListIterator<T> begin();
	CustomListIterator<T> end();

	CustomListIterator<T> rbegin();
	CustomListIterator<T> rend();
protected:
	CustomListNode<T>* GetLastNode();

private:
	size_t m_Size{ 0 };
	CustomListNode<T>* m_head{ nullptr };
};

template<typename T>
inline CustomList<T>::CustomList()
{
	m_head = new CustomListNode<T>();
}

template<typename T>
inline CustomList<T>::~CustomList()
{
	auto LastNode = GetLastNode();
	if (LastNode == nullptr)
	{
		return;
	}
	auto BehindNode = LastNode->behind;
	while (BehindNode)
	{
		delete LastNode;
		LastNode = BehindNode;
		BehindNode = LastNode->behind;
	}
}

template<typename T>
inline CustomListNode<T>* CustomList<T>::push(const T& _val)
{
	auto node = new CustomListNode<T>(_val);
	auto LastNode = GetLastNode();
	node->behind = LastNode;
	LastNode->next = node;
	++m_Size;
	return node;
}

template<typename T>
inline T CustomList<T>::pop()
{
	auto LastNode = GetLastNode();
	if (LastNode == m_head)
	{
		assert(0);
		return 0;
	}
	auto NowLastNode = LastNode->behind;
	NowLastNode->next = nullptr;
	T result = LastNode->_data;
	delete LastNode;
	--m_Size;
	return result;
}

template<typename T>
inline CustomListNode<T>* CustomList<T>::insert(CustomListNode<T>* node, T val)
{
	auto currentNode = m_head;
	while (currentNode->next != nullptr)
	{
		if (currentNode->next == node)
		{
			auto newNode = new CustomListNode<T>(val);
			newNode->behind = currentNode;
			newNode->next = node;
			currentNode->next = newNode;
			node->behind = newNode;			
			++m_Size;
			return newNode;
			break;
		}
		currentNode = currentNode->next;
	}
	return nullptr;
}

template<typename T>
inline int CustomList<T>::find(T val)
{
	int result = 0;
	CustomListNode<T>* findNode = m_head->next;
	while (findNode != nullptr && findNode->_data != val)
	{
		result++;
		findNode = findNode->next;
	}
	if (findNode == nullptr) {
		return -1;
	}
	return result;
}

template<typename T>
inline void CustomList<T>::remove(CustomListNode<T> *node)
{
	CustomListNode<T>* findNode = m_head->next;
	while (findNode != nullptr && findNode != node)
	{
		findNode = findNode->next;
	}

	if (findNode == nullptr)
	{
		return;
	}

	auto findNextNode = findNode->next;
	auto findBeforeNode = findNode->behind;
	delete findNode;
	findBeforeNode->next = findNextNode;
	if (findNextNode != nullptr)
	{
		findNextNode->behind = findBeforeNode;
	}
	--m_Size;
}

template<typename T>
inline void CustomList<T>::popAll()
{
	auto deleteNode = m_head->next;
	m_head->next = nullptr;
	while (deleteNode != nullptr)
	{
		auto temp = deleteNode->next;
		delete deleteNode;
		deleteNode = temp;
	}
	m_Size = 0;
}

template<typename T>
inline size_t CustomList<T>::Size()
{
	return m_Size;
}

template<typename T>
inline CustomListIterator<T> CustomList<T>::begin()
{
	return CustomListIterator<T>(m_head->next, m_head);
}

template<typename T>
inline CustomListIterator<T> CustomList<T>::end()
{
	return CustomListIterator<T>(nullptr, m_head);
}

template<typename T>
inline CustomListIterator<T> CustomList<T>::rbegin()
{
	return CustomListIterator<T>(GetLastNode(), GetLastNode(), true);
}

template<typename T>
inline CustomListIterator<T> CustomList<T>::rend()
{
	return CustomListIterator<T>(m_head, GetLastNode(), true);
}

template<typename T>
inline CustomListNode<T>* CustomList<T>::GetLastNode()
{
	if (m_head->next == nullptr)
	{
		return m_head;
	}
	CustomListNode<T>* node = m_head;
	do
	{
		node = node->next;
	} while (node && node->next);
	return node;
}